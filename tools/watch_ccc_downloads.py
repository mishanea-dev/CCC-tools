from pathlib import Path
from zipfile import ZipFile
import time
import re
import shutil

# EDIT: Change this to your active CCC edition folder.
EDITION_DIR = Path(r"C:\Programming\CCC\Testing\Edition X")
# WARNING: This script will modify the contents of the EDITION_DIR.
# Make sure you have a backup before running it.

# Set to False if you don't want the .cpp template to be created with each level's extraction.
insert_cpp_template = True

# Regular expression to match level-N.zip files, case-insensitive.
LEVEL_ZIP_PATTERN = re.compile(r"^level-(\d+)\.zip$", re.IGNORECASE)
# INFO: Does not require tinkering when used with CCC's official downloads.

# Path to the C++ template file. This file will be copied into each level's folder if insert_cpp_template is True.
TEMPLATE_FILE = Path(__file__).with_name("template.cpp")

# Folder to monitor for new Downloads
DOWNLOADS_DIR = Path.home() / "Downloads"
POLL_SECONDS = 2
STABLE_CHECKS_REQUIRED = 3

def matching_level_zip(path: Path):
    match = LEVEL_ZIP_PATTERN.match(path.name)
    return int(match.group(1)) if match else None

def wait_until_download_finishes(path: Path) -> bool:
    """Wait until the ZIP's size is unchanged for several checks."""
    previous_size = None
    stable_checks = 0

    while path.exists():
        try:
            current_size = path.stat().st_size
        except OSError:
            time.sleep(POLL_SECONDS)
            continue

        if current_size > 0 and current_size == previous_size:
            stable_checks += 1
            if stable_checks >= STABLE_CHECKS_REQUIRED:
                return True
        else:
            stable_checks = 0

        previous_size = current_size
        time.sleep(POLL_SECONDS)

    return False

def safe_extract(zip_path: Path, destination: Path):
    """Extract without allowing ZIP entries to escape the destination."""
    destination.mkdir(parents=True, exist_ok=True)
    destination_resolved = destination.resolve()

    with ZipFile(zip_path) as archive:
        for member in archive.infolist():
            output_path = (destination / member.filename).resolve()

            # Protect against paths such as ../../outside.txt in the ZIP.
            if output_path != destination_resolved and destination_resolved not in output_path.parents:
                raise ValueError(f"Unsafe path in ZIP: {member.filename}")

            # Do not silently replace files already in your project.
            if output_path.exists() and not member.is_dir():
                raise FileExistsError(f"File already exists: {output_path}")

        archive.extractall(destination)

def main():
    # Check for the Downlods folder
    if not DOWNLOADS_DIR.is_dir():
        raise SystemExit(f"Downloads folder not found: {DOWNLOADS_DIR}, Exiting.")

    # Check for the edition folder and create it if it doesn't exist
    if not EDITION_DIR.is_dir():
        print(f"Edition folder not found: {EDITION_DIR}")
        makedirs = input(f"Do you want to create it? (y/n): ").strip().lower()
        if makedirs == 'y':
            EDITION_DIR.mkdir(parents=True, exist_ok=True)
            print(f"Created edition folder: {EDITION_DIR}")
            if not EDITION_DIR.is_dir():
                raise SystemExit(f"Failed to create edition folder: {EDITION_DIR}, Exiting.")
        else:
            raise SystemExit(f"Edition folder unavailable: {EDITION_DIR}, Exiting.")


    # Check for the template file if use_cpp_template is True
    use_cpp_template = insert_cpp_template
    if use_cpp_template and not TEMPLATE_FILE.is_file():
        print(f"Template file not found: {TEMPLATE_FILE}")
        giveup_template = input("Do you want to continue without automatic .cpp template creation? (y/n):").strip().lower()
        if giveup_template == 'y':
            use_cpp_template = False
            print(f"Continuing without automatic .cpp template creation.")
        else:
            raise SystemExit(f"Make sure the template file exists: {TEMPLATE_FILE}, Exiting.")

    # Don't process ZIPs that were already in Downloads when the watcher started.
    seen = {p.resolve() for p in DOWNLOADS_DIR.glob("*.zip")}

    print(f"Watching: {DOWNLOADS_DIR}")
    print(f"Extracting into:  {EDITION_DIR}")
    print("Waiting for newly downloaded level-N.zip files. Press Ctrl+C to stop.")

    while True:
        for zip_path in DOWNLOADS_DIR.glob("*.zip"):
            level = matching_level_zip(zip_path)

            if level is None or zip_path.resolve() in seen:
                continue

            print(f"\nDetected: {zip_path.name} - waiting for download to finish...")
            if not wait_until_download_finishes(zip_path):
                seen.add(zip_path.resolve())
                continue

            level_dir = EDITION_DIR / f"level_{level}"
            destination = level_dir

            try:
                safe_extract(zip_path, destination)
                print(f"Extracted to: {destination}")

                if use_cpp_template:
                    source_file = level_dir / f"level_{level}.cpp"

                    try:
                        if source_file.exists():
                            raise FileExistsError(source_file)

                        shutil.copy2(TEMPLATE_FILE, source_file)
                        print(f"Created source file: {source_file}")
                    except FileExistsError:
                        print(f"Source file already exists, leaving it unchanged: {source_file}")
                    except Exception as error:
                        print(f"Could not create source file: {error}")

            except FileExistsError as error:
                print(f"Skipped to avoid overwriting: {error}")
            except Exception as error:
                print(f"Could not extract {zip_path.name}: {error}")

            seen.add(zip_path.resolve())

        time.sleep(POLL_SECONDS)

if __name__ == "__main__":
    main()
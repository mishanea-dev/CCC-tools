from pathlib import Path
from zipfile import ZipFile
import time
import re

# Change this to your active CCC edition folder.
EDITION_DIR = Path(r"C:\Programming\CCC\42th Edition")
# EDITION_DIR = Path(r"C:\Programming\CCC\Practice\ASTEROID_MINING")

LEVEL_ZIP_PATTERN = re.compile(r"^level-(\d+)\.zip$", re.IGNORECASE)

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
    if not EDITION_DIR.is_dir():
        raise SystemExit(f"Edition folder not found: {EDITION_DIR}")

    # Don't process ZIPs that were already in Downloads when the watcher started.
    seen = {p.resolve() for p in DOWNLOADS_DIR.glob("*.zip")}

    print(f"Watching: {DOWNLOADS_DIR}")
    print(f"Edition:  {EDITION_DIR}")
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

                source_file = level_dir / f"level_{level}.cpp"
                try:
                    source_file.touch(exist_ok=False)
                    print(f"Created source file: {source_file}")
                except FileExistsError:
                    print(f"Source file already exists, leaving it unchanged: {source_file}")
            except FileExistsError as error:
                print(f"Skipped to avoid overwriting: {error}")
            except Exception as error:
                print(f"Could not extract {zip_path.name}: {error}")

            seen.add(zip_path.resolve())

        time.sleep(POLL_SECONDS)

if __name__ == "__main__":
    main()
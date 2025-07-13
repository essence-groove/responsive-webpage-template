#
 # Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward) (https://github.com/apm-essence-groove/apm-essence-groove-ci-cd)
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Affero General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU Affero General Public License for more details.
 #
 # You should have received a copy of the GNU Affero General Public License
 # along with this program.  If not, see <https://www.gnu.org/licenses/>.
 #


import json
import os
import sys

def main():
    # --- Retrieve Writable Files Secret ---
    rwt_writable_files_str = os.environ.get("RWT_WRITABLE_FILES")
    allowed_write_paths = []
    if rwt_writable_files_str:
        allowed_write_paths = [os.path.normpath(p.strip()) for p in rwt_writable_files_str.split(',') if p.strip()]
    
    def is_write_allowed(target_path):
        normalized_target_path = os.path.normpath(target_path)
        for allowed_path in allowed_write_paths:
            if normalized_target_path == allowed_path:
                return True
        print(f"::warning::SECURITY ALERT: Attempted to write to '{target_path}', but it is not listed in RWT_WRITABLE_FILES secret. Write operation skipped.", file=sys.stderr)
        print(f"::warning::Please update the 'RWT_WRITABLE_FILES' secret with a comma-separated list of allowed file paths (e.g., 'apps.md,homepage-app/apps/apps.json') if this write is intended.", file=sys.stderr)
        return False

    # --- Data Collection Logic ---
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    apps_data = [] # List to hold dictionaries for each app
    apps_updated_flag_json = False # Track if json content was generated

    for app_dir in app_dirs:
        app_folder_name = os.path.basename(app_dir)
        package_json_path = os.path.join(app_dir, "package.json")
        
        if not os.path.exists(package_json_path):
            print(f"::warning::package.json not found for {app_folder_name} at {app_dir}. Skipping.", file=sys.stderr)
            continue

        try:
            with open(package_json_path, "r") as f:
                package_json_data = json.load(f)
            
            app_url = package_json_data.get("deployedUrl") 
            
            if not app_url: 
                print(f"::warning::Skipping JSON entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json.", file=sys.stderr)
                continue
            
            # Add app data to the list
            apps_data.append({
                "name": app_folder_name,
                "url": app_url
            })
            apps_updated_flag_json = True # Set to true if at least one app is added

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # --- Generate apps.json File ---
    json_output_dir = os.path.join("homepage-app", "apps")
    json_output_file_path = os.path.join(json_output_dir, "apps.json")

    # Only write if permission is granted via secret
    if is_write_allowed(json_output_file_path):
        os.makedirs(json_output_dir, exist_ok=True) # Ensure directory exists
        try:
            with open(json_output_file_path, "w") as f:
                json.dump(apps_data, f, indent=2) # Use indent=2 for pretty-printing
            print(f"::notice::Successfully generated {json_output_file_path}")
        except Exception as e:
            print(f"::error::Failed to write {json_output_file_path}: {e}", file=sys.stderr)
            sys.exit(1)
    else:
        apps_updated_flag_json = False # Mark as not updated if write was skipped

    # Output a flag for the apps.json generation status
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_json_updated_flag={str(apps_updated_flag_json).lower()}\n")


if __name__ == "__main__":
    main()

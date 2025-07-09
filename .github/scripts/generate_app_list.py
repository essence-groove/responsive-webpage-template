import json
import os
import sys

def main():
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    # --- ADDED EXTRA NEWLINES FOR SPACING ---
    apps_md_content = "# 🚀 Deployed Applications\n\n" # Two newlines after heading
    apps_md_content += "This file lists the applications deployed from this repository to Heroku.\n\n" # Two newlines after intro text
    apps_md_content += "## App List\n\n" # Two newlines after sub-heading
    # --- END ADDITIONS ---
    
    apps_updated_flag = False

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
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json. Please add it.", file=sys.stderr)
                continue
            
            apps_md_content += f"* **{app_folder_name}:** [{app_url}]({app_url})\n\n" # --- ADDED EXTRA NEWLINE HERE ---
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # Corrected escaping for GITHUB_OUTPUT. 
    # This remains critical for GitHub Actions to correctly interpret newlines.
    final_escaped_content = apps_md_content.replace("%", "%25").replace("\n", "%0A").replace("\r", "%0D")
    
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content={final_escaped_content}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")

if __name__ == "__main__":
    main()

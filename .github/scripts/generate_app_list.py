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

    apps_md_content = "# 🚀 Deployed Applications\n\n"
    apps_md_content += "This file lists the applications deployed from this repository to Heroku.\n\n"
    apps_md_content += "## App List\n\n"
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
            
            # --- READ THE NEW 'deployedUrl' FIELD ---
            app_url = package_json_data.get("deployedUrl") 
            
            if not app_url: # Check for empty or missing deployedUrl
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json. Please add it.", file=sys.stderr)
                continue
            
            # --- Removed Heroku app name and URL construction, using 'deployedUrl' directly ---
            apps_md_content += f"* **{app_folder_name}:** [{app_url}]({app_url})\\n"
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # Output the generated content and a flag indicating if there's anything to write
    # FIX: Corrected escaping for GITHUB_OUTPUT. 
    # Python's default string escaping for GITHUB_OUTPUT is usually fine,
    # but the previous sed commands were problematic.
    # The key is to avoid unnecessary escaping and let GitHub Actions handle it.
    
    # We will write directly to the GITHUB_OUTPUT file, ensuring each key-value pair is on its own line.
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        # Encode newlines for GITHUB_OUTPUT as it expects a single-line string.
        # Use Python's replace for explicit encoding if needed, or let GitHub handle it.
        # Let's try direct print, as GitHub Actions often handles this itself.
        
        # Simpler and more direct output without sed replacements:
        # GitHub Actions typically handles the %0A, %0D, %25 internally for multi-line outputs
        # when you print to stdout or write directly to $GITHUB_OUTPUT.
        # The previous sed commands were re-escaping, leading to garbled text.
        
        # First, ensure the content itself has literal newlines for the file,
        # then rely on GitHub's built-in output mechanism.
        
        # Replace Python's '\n' with literal newlines for the output file
        # and then let GHA handle its internal escaping for app_dirs_json:
        apps_md_content_for_output = apps_md_content.replace("\\n", "\n") 
        
        # For multiline output, GitHub recommends using `\n` in Python and letting it handle it,
        # or using a temporary file. Since we need to assign it to an environment variable in the shell,
        # manual encoding is often safer.

        # Re-introducing the recommended escaping for GITHUB_OUTPUT, which was previously correct
        # but might have been applied multiple times, leading to issues.
        # The Python script handles the initial generation of content, then escapes it for output.
        escaped_content = apps_md_content.replace("\n", "%0A").replace("\r", "%0D").replace("%", "%25")
        
        output_file.write(f"apps_md_section_content={escaped_content}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")


if __name__ == "__main__":
    main()

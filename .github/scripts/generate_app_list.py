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
            
            # --- Ensure 'deployedUrl' is read directly ---
            app_url = package_json_data.get("deployedUrl") 
            
            if not app_url: # Check for empty or missing deployedUrl
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json. Please add it.", file=sys.stderr)
                continue
            
            # --- Use the actual URL from package.json ---
            apps_md_content += f"* **{app_folder_name}:** [{app_url}]({app_url})\n"
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # --- FIX: Simplified escaping for GITHUB_OUTPUT ---
    # GitHub Actions typically handles multiline output directly if printed line by line
    # or if the variable contains literal newlines.
    # The previous string replacements were likely double-escaping.
    
    # Ensure the content has literal newlines for the output file
    final_content_for_output = apps_md_content.replace("\\n", "\n") 
    
    # Write directly to $GITHUB_OUTPUT file for clean multiline output
    # Each print statement adds a new line, so ensure format is 'key=value'.
    # GitHub Actions will then handle the decoding of content_type=text/plain; for multiline.
    
    # The most reliable way for multiline output is to set a variable directly in the workflow's run command
    # using a specific syntax, or using a temporary file.

    # Let's revert to a simpler, more direct way of setting the output,
    # as the previous complex escaping was the cause of garbled text.
    # We will rely on GitHub Actions' recent improvements for multiline string outputs.
    
    # For GITHUB_OUTPUT, the value *must* be a single line.
    # Therefore, we still need to replace newlines with %0A etc.
    # However, the previous `sed` commands might have been compounding the issue.

    # Let's ensure the Python script creates the *final escaped string* properly.
    # The initial `apps_md_content` uses `\n` which Python converts to literal newlines.
    # For the `GITHUB_OUTPUT` file, these newlines must be re-escaped.

    # This escape is actually necessary for `GITHUB_OUTPUT` to parse multiline strings correctly.
    # The problem might have been in the Bash script then, when it consumed it.
    
    # Let's make sure the script explicitly adds the `\n` to the end of the line for output,
    # and then encodes it. The issue may have been with `sed` or `echo` in the Bash script.
    
    # --- Corrected escaping for GITHUB_OUTPUT from Python ---
    # Python strings use '\n' for newline. When passing to GITHUB_OUTPUT, this needs conversion.
    # %0A is the correct escape for a newline in GITHUB_OUTPUT variable values.
    # %25 is the correct escape for a literal '%' character.
    final_escaped_content = apps_md_content.replace("%", "%25").replace("\n", "%0A").replace("\r", "%0D")
    
    # Write directly to $GITHUB_OUTPUT file
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content={final_escaped_content}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")

if __name__ == "__main__":
    main()

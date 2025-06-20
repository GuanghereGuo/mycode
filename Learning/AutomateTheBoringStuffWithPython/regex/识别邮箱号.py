import pyperclip, re

email_regex = re.compile(r'([\w-]+(\.[\w-]+)*@(\w+)(\.[\w-]+)+)')

text = str(pyperclip.paste())
matches = []
for groups in email_regex.findall(text):
    email = groups[0]
    matches.append(email)

if len(matches) > 0:
    pyperclip.copy('\n'.join(matches))
    print('Copied to clipboard:')
    print('\n'.join(matches))

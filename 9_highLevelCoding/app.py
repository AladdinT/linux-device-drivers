
with open('/dev/my_file', 'r') as file:
    content = file.read()
    print("Read from /dev/my_file:", content)

with open('/dev/my_file', 'w') as file:
    data_to_write = "Hello from Python!"
    file.write(data_to_write)
    print("Write to /dev/my_file:", data_to_write)

with open('/dev/my_file', 'r') as file:
    updated_content = file.read()
    print("Updated content of /dev/my_file:", updated_content)

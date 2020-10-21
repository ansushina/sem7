from subprocess import check_output
import hashlib
import os.path

def get_checksum():
    output = check_output("wmic csproduct get UUID", shell=True).decode()
    hard_uuid = output.split("\n")[1]
    return hashlib.sha512(hard_uuid.encode('utf-8')).hexdigest()


def check_checksum(filename):
    if not os.path.isfile(filename):
        return False
    with open(filename, "r") as license:
        if license.readline() == get_checksum():
            return True
        else:
            return False


def create_license(filename):
    with open(filename, "w") as license:
        license.write(get_checksum())


if __name__ == "__main__":
    create_license("license.key")
    with open("license.key", "r") as license:
        print(license.readline())

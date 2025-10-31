import json
import re

class Parser:

    def __init__(self, file):
        self.file = file

    def parse_json(self):
        with open(self.file, "r") as json_file:
            config_dict = json.load(json_file)

        pattern = r'/([^/]+)\.json$'
        match = re.search(pattern, self.file)

        return config_dict, match.group(1)

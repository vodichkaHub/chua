import yaml
import os
import subprocess

def makeInputFile(input_filename: str, data: dict):
    with open(input_filename, 'w') as stream:
        yaml.dump(data, stream)

def runModel(model_filename: str, input_filename: str, chanel_signal_filename: str, restored_filename: str):
    subprocess.call([model_filename, input_filename, chanel_signal_filename, restored_filename])

def getRestoredSignal(restored_filename: str) -> list:
    with open(restored_filename, 'r') as stream:
        data = yaml.safe_load(stream)['restored']
        return list(map(str, data))

# HEAVY FUNCTION!!! time consuming
def getChanelData(chanel_signal_filename) -> dict:
    chanel_data = {'x1': [], 'x2': [], 'x3': []}
    with open(chanel_signal_filename, 'r') as stream:
        yaml_data = yaml.safe_load(stream)
        chanel_data['x1'] = [yaml_data['x1'][i] for i in range(len(yaml_data['x1'])) if i % 1000 == 0]
        chanel_data['x2'] = [yaml_data['x2'][i] for i in range(len(yaml_data['x1'])) if i % 1000 == 0]
        chanel_data['x3'] = [yaml_data['x3'][i] for i in range(len(yaml_data['x1'])) if i % 1000 == 0]
    return chanel_data
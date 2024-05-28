import yaml
import os
import subprocess
import matplotlib.pyplot as plt

cur_dir = os.path.dirname(os.path.realpath(__file__))

# SET INPUT DATA HERE
data_to_transmit = {'signal': [1,0,1,0,1,0]}

# WRITE INPUT DATA TO A FILE
input_filename = os.path.join(cur_dir, 'input_signal.yaml')
with open(input_filename, 'w') as stream:
    yaml.dump(data_to_transmit, stream)

# CALL EXECUTABLE SIMULNIK MODEL HERE. IT TAKES SOME TIME
exec_filename  =  os.path.join(cur_dir, '..', 'build', 'example')
subprocess.call([exec_filename, input_filename])

# READ RESTORED SIGNAL HERE
restored_signal_filename=  os.path.join(cur_dir, '..', 'restored_signal.yaml')
restored_data = []
with open(restored_signal_filename, 'r') as stream:
    restored_data = yaml.safe_load(stream)['restored']

# VISUALIZE RESTORED SIGNAL HERE
print(data_to_transmit['signal'])
print(restored_data)

# READ ENCRYPTED SIGNAL HERE
chanel_signal_filename=  os.path.join(cur_dir, '..', 'encrypted_signal.yaml')
chanel_data = [[],[],[]]
with open(chanel_signal_filename, 'r') as stream:
    yaml_data = yaml.safe_load(stream)
    chanel_data[0] = yaml_data['x1']
    chanel_data[1] = yaml_data['x2']
    chanel_data[2] = yaml_data['x3']
# print(chanel_data)

# VISUALIZE ENCRYPTED SIGNAL HERE
samples = range(0,len(chanel_data[0]))
fig = plt.figure()
axes = fig.subplots(nrows=3, ncols=1, sharey=True)
for i in range(0,3):
    axes[i].plot(samples, chanel_data[i])
    axes[i].grid(True)
plt.show()
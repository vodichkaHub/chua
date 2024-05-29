import sys
import os
from PyQt5 import QtWidgets # pip install PyQt5
import chua_ui  # Это файл дизайна
from string import ascii_letters, punctuation  # pip install strings

import simulink
import matplotlib.pyplot as plt

class ExampleApp(QtWidgets.QMainWindow, chua_ui.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.runButton.clicked.connect(self.startFunc)

    def modelRun(self, bytesin: list) -> list:
        # simulink
        bytelist_out = []
        chanel_data_plot = {'x1': [], 'x2': [], 'x3': []}
        cur_dir = os.path.dirname(os.path.realpath(__file__))
        input_file = os.path.join(cur_dir, '..', 'run', 'input_signal.yaml')
        chanel_data_file = os.path.join(cur_dir, '..', 'run', 'encrypted_signal.yaml')
        restored_file = os.path.join(cur_dir, '..', 'run', 'restored_signal.yaml')
        model_exe  =  os.path.join(cur_dir, '..', 'build', 'example')
        for byte_letter in bytesin:
            simulink.makeInputFile(input_file, {'signal': byte_letter})
            simulink.runModel(model_exe, input_file, chanel_data_file, restored_file)
            bytelist_out.append(simulink.getRestoredSignal(restored_file))
            # chanel_data = simulink.getChanelData(chanel_data_file)
            # chanel_data_plot['x1'].extend(chanel_data['x1'])
            # chanel_data_plot['x2'].extend(chanel_data['x2'])
            # chanel_data_plot['x3'].extend(chanel_data['x3'])
        # simulink

        # names = ['x1', 'x2', 'x3']
        # samples = range(0,len(chanel_data_plot['x1']))
        # fig = plt.figure()
        # axes = fig.subplots(nrows=3, ncols=1, sharey=True)
        # for i in range(0,3):
        #     axes[i].plot(samples, chanel_data_plot[names[i]])
        #     axes[i].grid(True)
        # plt.draw()
        # plt.pause(.001)

        return bytelist_out

    def startFunc(self):
        # Получаем текст
        textin = self.userTextInput.toPlainText()
        # print(textin)
        #Делаем бинарным каждый символ и по букву объединяет в списки
        bytelist = [list(format(ord(x), 'b')) for x in textin]
        # print(bytelist)

        # simulink model
        bytelist_out = self.modelRun(bytelist)

        # Отдаём текст, превращая из bytelist в нормальное слово
        textout = ''.join(chr(int(''.join(byte), 2)) for byte in bytelist_out)
        self.systemTextOutput.setPlainText(textout)

    def encode(message):
        encode_data = {letter: bin(ord(letter)) for letter in ascii_letters + punctuation + ' '}
        return [encode_data[letter] for letter in message]

    def decode(table):
        decode_data = {bin(ord(letter)): letter for letter in ascii_letters + punctuation + ' '}
        return [decode_data[item] for item in table]

def main():
    app = QtWidgets.QApplication(sys.argv)  # Новый экземпляр QApplication
    window = ExampleApp()
    window.show()
    app.exec_()

if __name__ == '__main__':
    main()
# -*- coding: utf-8 -*-
from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)

        self.centralwidget.setObjectName("centralwidget")
        self.userTextInput = QtWidgets.QTextEdit(self.centralwidget)
        self.userTextInput.setGeometry(QtCore.QRect(10, 10, 291, 281))

        self.userTextInput.setObjectName("userTextInput")
        self.systemTextOutput = QtWidgets.QTextBrowser(self.centralwidget)
        self.systemTextOutput.setGeometry(QtCore.QRect(470, 10, 321, 281))

        self.systemTextOutput.setObjectName("systemTextOutput")
        self.runButton = QtWidgets.QPushButton(self.centralwidget)
        self.runButton.setGeometry(QtCore.QRect(310, 110, 151, 81))

        self.runButton.setObjectName("runButton")
        self.graphicsViewX1 = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsViewX1.setGeometry(QtCore.QRect(10, 300, 781, 91))

        self.graphicsViewX1.setObjectName("graphicsViewX1")
        self.graphicsViewX2 = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsViewX2.setGeometry(QtCore.QRect(10, 390, 781, 91))
        self.graphicsViewX2.setObjectName("graphicsViewX2")
        self.graphicsViewX3 = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsViewX3.setGeometry(QtCore.QRect(10, 480, 781, 91))
        self.graphicsViewX3.setObjectName("graphicsViewX3")

        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "ШифроЧуа"))
        self.userTextInput.setHtml(_translate("MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:\'MS Shell Dlg 2\'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"))
        self.runButton.setText(_translate("MainWindow", "Запустить"))
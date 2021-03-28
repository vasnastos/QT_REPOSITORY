from PySide6.QtWidgets import *
import PySide6.QtCore as qt
from PySide6.QtGui import * 
from rps import *
import sys
import logging as log

logger=log.getLogger('Match Logegr')
logger.setLevel(log.DEBUG)
fh=log.FileHandler('rps.log','w')
sh=log.StreamHandler()
formatter=log.Formatter(' *%(asctime)s\n *%(levelname)s\n *%(message)s \n')
fh.setFormatter(formatter)
sh.setFormatter(formatter)
logger.addHandler(fh)
logger.addHandler(sh)


playerscoreLabel='font-size:18px;'
computerscorelabel='font-size:21px; margin-left:30px;'

RPS={'Rock':'R','Paper':'P','Scissors':'S'}
RPS_PHOTO={'R':'RESOURCES/rock.png','S':'RESOURCES/scissors.png','P':'RESOURCES/paper.png'}
colors={'W':'#0f5430','L':'#780714','T':'#1b39a6'}

class window(QMainWindow):
    def make_menu(self):
       self.menu=QMenu('OPTIONS')
       a1=QAction(QIcon('RESOURCES/summary.jpg'),'SUMMARY',self)
       a2=QAction(QIcon('RESOURCES/quit.png'),'QUIT',self)
       self.menu.addAction(a1)
       a1.triggered.connect(lambda:self.summary())
       self.menu.addAction(a2)
       a2.triggered.connect(lambda:self.Exit())
       self.menuBar().addMenu(self.menu)

    def __init__(self,):
        QMainWindow.__init__(self,None)
        self.gm=game()
        self.setFixedSize(500,500)
        self.make_menu()
        self.setWindowTitle('RPS GAME')
        self.cw=QWidget()
        self.setCentralWidget(self.cw)
        self.setWindowIcon(QIcon('.RESOURCES/central.png'))
        self.lay=QVBoxLayout()
        self.number_of_rounds=QInputDialog.getInt(self,'Number of Rounds','<b style=\"color:blue; font-size:18px;\">Give Number of Rounds</b>')
        self.roundcounter=1
        self.cw.setLayout(self.lay)
        lb=QLabel()
        lb.setFixedSize(0.96*self.width(),0.2*self.height())
        lb.setAlignment(qt.Qt.AlignCenter)
        lb.setPixmap(QPixmap('RESOURCES/RPS.png').scaled(lb.width(),lb.height()))
        self.lay.addWidget(lb)
        self.move=QComboBox()
        self.move.setFixedWidth(0.2*self.width())
        self.move.setStyleSheet('border:2px solid; background-color:white; color:black; text-align:center; font-size:18px;')
        self.move.activated.connect(lambda:self.round())
        list=['Rock','Paper','Scissors']
        self.move.addItems(list)
        self.cmove=QLineEdit()
        self.cmove.setEnabled(False)
        self.cmove.setFixedWidth(0.2*self.width())
        self.cmove.setStyleSheet('border:2px solid; background-color:white; color:black; text-align:center; font-size:18px;')
        l2=QHBoxLayout()
        l2.setSpacing(5)
        l2.addWidget(self.move)
        l2.addWidget(self.cmove)
        self.lay.addLayout(l2)
        self.picon=QLabel()
        self.picon.setFixedSize(0.4*self.width(),0.5*self.height())
        self.picon.setStyleSheet('border-collapse:collapse;')
        self.cicon=QLabel()
        self.cicon.setFixedSize(0.4*self.width(),0.5*self.height())
        self.cicon.setStyleSheet('border-collapse:collapse;')
        movie=QMovie()
        movie.setFileName('RESOURCES/rps.gif')
        size=qt.QSize(self.cicon.width(),self.cicon.height())
        movie.setScaledSize(size)
        self.cicon.setMovie(movie)
        self.picon.setMovie(movie)
        self.cicon.movie().start()
        self.picon.movie().start()
        l3=QHBoxLayout()
        l3.addWidget(self.picon)
        l3.addWidget(self.cicon)
        self.lay.addLayout(l3)
        l4=QHBoxLayout()
        self.playerscore=QLabel('Player:0')
        self.computerscore=QLabel('Computer:0')
        self.playerscore.setFixedSize(0.17*self.width(),0.1*self.height())
        self.computerscore.setFixedSize(0.3*self.width(),0.1*self.height())
        self.playerscore.setAlignment(qt.Qt.AlignLeft)
        self.computerscore.setAlignment(qt.Qt.AlignLeft)
        self.playerscore.setStyleSheet(playerscoreLabel)
        self.computerscore.setStyleSheet(computerscorelabel)
        l4.setSpacing(15)
        l4.addWidget(self.playerscore,4)
        l4.addWidget(self.computerscore,4)
        self.lay.addLayout(l4)
    
    def reset_Game(self):
        movie=QMovie()
        movie.setFileName('RESOURCES/rps.gif')
        size=qt.QSize(self.cicon.width(),self.cicon.height())
        movie.setScaledSize(size)
        self.cicon.setMovie(movie)
        self.picon.setMovie(movie)
        self.cicon.movie().start()
        self.picon.movie().start()
        self.playerscore.setText('Player:0')
        self.computerscore.setText('Computer:0')
        self.roundcounter=1
        self.gm.plc=0
        self.gm.plcm=0
        self.number_of_rounds=QInputDialog.getInt(self,'Number of Rounds','<b style=\"color:blue; font-size:18px;\">Give Number of Rounds</b>')

    def round(self):
        logger.info('Winner:'+str(self.gm.round(RPS[str(self.move.currentText())])))
        result=self.gm.Result()
        self.cmove.setText(self.gm.Computer())
        self.picon.setPixmap(QPixmap(RPS_PHOTO[RPS[self.move.currentText()]]).scaled(self.picon.width(),self.picon.height()))
        self.cicon.setPixmap(QPixmap(RPS_PHOTO[self.gm.CharComputer()]).scaled(self.cicon.width(),self.cicon.height()))
        self.playerscore.setText('Player:'+str(self.gm.playerWins()))
        self.computerscore.setText('Computer:'+str(self.gm.computerWins()))
        if str(result)=='P':
            self.playerscore.setStyleSheet(playerscoreLabel+' color:'+colors['W']+';')
            self.computerscore.setStyleSheet(computerscorelabel+' color:'+colors['L']+';')
        elif str(result)=='C':
            self.playerscore.setStyleSheet(playerscoreLabel+' color:'+colors['L']+';')
            self.computerscore.setStyleSheet(computerscorelabel+' color:'+colors['W']+';')
        else:
            self.playerscore.setStyleSheet(playerscoreLabel)
            self.computerscore.setStyleSheet(computerscorelabel)
        self.roundcounter+=1
        if int(self.roundcounter)>int(self.number_of_rounds[0]):
            QMessageBox.information(self,'Winner',self.gm.Summary())
            i=QMessageBox.information(self,'Game Ended','<b>Start a new Game?',QMessageBox.Yes,QMessageBox.No)
            if int(i)==QMessageBox.Yes:
                logger.info(self.gm.Summary().strip())
                self.reset_Game()
            else:
                sys.exit(0)

    def summary(self):
        print('Summary')
    def Exit(self):
        sys.exit(0)

def main():
    a=QApplication()
    w=window()
    w.show()
    return a.exec_()

if __name__=='__main__':
    main()

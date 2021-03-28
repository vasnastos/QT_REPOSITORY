import random as r

available=['R','P','S']
name={'R':'Rock','P':'Paper','S':'Scissors'}

class game:
    def __init__(self):
        self.player=''
        self.computer=''
        self.result=''
        self.plc=0
        self.plcm=0
    def round(self,pl):
        self.player=pl
        pos=r.randint(0,2)
        self.computer=available[int(pos)]
        if str(self.player)==str(self.computer):
            self.result='T'
            return 'Tie Game'
        elif str(self.player)=='R' and str(self.computer)=='S':
            self.result='P'
            self.plc+=1
            return 'Player wins'
        elif str(self.player)=='S' and str(self.computer)=='P':
            self.result='P'
            self.plc+=1
            return 'Player wins'
        elif str(self.player)=='P' and str(self.computer)=='R':
            self.result='P'
            self.plc+=1
            return 'Player wins'
        else:
            self.plcm+=1
            self.result='C'
            return 'Computer wins'
    def Computer(self):
        return name[str(self.computer)]
    def CharComputer(self):
        return self.computer
    def Result(self):
        return self.result
    def playerWins(self):
        return self.plc
    def computerWins(self):
        return self.plcm
    def Summary(self):
        colorplayer='black'
        colorcomputer='black'
        fontpl='17px;'
        fontcm='17px;'
        if int(self.plc)>int(self.plcm):
            colorplayer='green'
            colorcomputer='red'
            fontpl='21px;'
            fontcm='18px;'
        elif int(self.plc)<int(self.plcm):
            colorplayer='red'
            colorcomputer='green'
            fontpl='18px;'
            fontcm='21px;'
        return f"""
        <b style=\"color:{colorplayer}; font-size:{fontpl}\">Player:{self.plc}</b><br>
        <b style=\"color:{colorcomputer}; font-size:{fontcm}\">Computer:{self.plcm}</b><br><br>
        """
from src.wator.WAgent import WAgent

class Shark(WAgent):
    def __init__(self, posX, posY, data):
        # position initiale de la particule
        super(Shark, self).__init__(posX, posY)

        # Gestation
        self.gestationDay = data[0]
        self.deadTime =data[1]
        self.hungry = 0
        self.color = "pink"


    def decide(self, env):
        self.gestation += 1
        self.age += 1
        self.change = False
        self.color = "red"

        positions = env.moore(self.posX, self.posY)
        # newPos = env.near(self.posX, self.posY)

        for pos in positions :
            if (pos[1] == None): # si le requin peut bouger
                self.updatePosition(env, pos[0], Shark, [self.gestationDay, self.deadTime])
                return
            elif(pos[1].getType() == 1): # si le requin peut monger
                self.hungry = 0
                env.dead(pos[0][0], pos[0][1])
                self.updatePosition(env, pos[0], Shark, [self.gestationDay, self.deadTime])
                return

        self.hungry +=1 # sinon il a faim
        if(self.hungry>=self.deadTime): # et il meurt
            env.dead(self.posX, self.posY)
            return

    def getType(self):
        return 2

    def getColorBorn(self):
        return "pink"

    def getColor(self):
        return "red"

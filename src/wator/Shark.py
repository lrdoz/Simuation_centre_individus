from src.wator.WAgent import WAgent

"""
Implémentation d'un agent ayant le comportement d'un requin
"""
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
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.gestation += 1
        self.age += 1
        self.change = False

        if (self.age >= 2):
            self.change = True
            self.color = "red"

        self.hungry +=1 # sinon il a faim
        if(self.hungry>=self.deadTime): # et il meurt
            env.kill(self.posX, self.posY)
            return

        positions = env.moore(self.posX, self.posY)
        poslibres = []
        # newPos = env.near(self.posX, self.posY)

        for pos in positions :
            if (pos[1] != None and pos[1].getType() == 1): # si le requin peut monger
                self.hungry = 0
                env.kill(pos[0][0], pos[0][1])
                self.updatePosition(env, pos[0], Shark, [self.gestationDay, self.deadTime])
                return
            if (pos[1] == None):
                poslibres.append(pos)

        if poslibres :
            self.updatePosition(env, poslibres[0][0], Shark, [self.gestationDay, self.deadTime])


    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 2

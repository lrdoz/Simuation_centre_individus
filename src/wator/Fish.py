from src.wator.WAgent import WAgent

class Fish(WAgent):
    def __init__(self, posX, posY, data):
        # position initiale de la particule
        super(Fish, self).__init__(posX, posY)

        # Gestation
        self.gestationDay = data[0]


    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.gestation+=1
        self.age +=1

        positions = env.moore()

        for case in positions:
            if case[1] == None:
                self.updatePosition(env, case[0], Fish, [self.gestationDay])
                return

    def getType(self):
        return 1

    def getColorBorn(self):
        return "yellow"

    def getColor(self):
        return "green"

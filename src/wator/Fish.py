from src.wator.WAgent import WAgent

"""
Implémentation d'un agent ayant le comportement d'un poisson
"""
class Fish(WAgent):
    def __init__(self, posX, posY, data):
        # position initiale de la particule
        super(Fish, self).__init__(posX, posY)

        # Gestation
        self.gestationDay = data[0]
        self.color = "yellow"


    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.gestation+=1
        self.age +=1
        self.change = False

        if (self.age >= 2):
            self.change = True
            self.color = "green"

        positions = env.moore(self.posX, self.posY) # on regarde les voisins du petit poisson

        for case in positions:
            if case[1] == None:

                self.updatePosition(env, case[0], Fish, [self.gestationDay])
                return

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 1

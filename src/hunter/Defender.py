from src.core.Agent import Agent

"""
"""
class Defender(Agent):
    def __init__(self, posX, posY, data):
        # position initiale de l'avatar
        super(Defender, self).__init__(posX, posY)

        self.form = "circle"
        self.deadLine = data[0]
        self.natural = False

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.time += 1

        if self.deadLine <= self.time:
            self.natural = True
            self.dead()

    def getColor(self):
        """
        Retourne la couleur de l'agent

        :return: Couleur de l'agent
        """
        return "green"

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 3

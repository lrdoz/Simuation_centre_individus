from src.core.Agent import Agent

"""
Implémentation d'un agent ayant le comportement d'un defender
"""
class Defender(Agent):
    def __init__(self, posX, posY, data):
        # position initiale de l'avatar
        super(Defender, self).__init__(posX, posY)

        self.form = "circle"
        self.deadLine = data[0]
        self.natural = False
        self.color = "green"

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.time += 1

        if self.deadLine <= self.time:
            self.natural = True
            self.dead()

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 3

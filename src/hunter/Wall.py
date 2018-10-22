from src.core.Agent import Agent

"""
Implémentation d'un agent ayant le comportement d'un mur
"""
class Wall(Agent):
    def __init__(self, posX, posY, data=[]):
        # position initiale de la particule
        super(Wall, self).__init__(posX, posY)
        self.form = "rectangle"

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        pass

    def getColor(self):
        """
        Retourne la couleur de l'agent

        :return: Couleur de l'agent
        """
        return "black"

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 1

from src.core.Agent import Agent
import sys

"""
"""
class Winner(Agent):
    def __init__(self, posX, posY, data=[]):
        # position initiale de l'avatar
        super(Winner, self).__init__(posX, posY)

        self.form = "circle"

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
        return "blue"

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 4

    def dead(self):
        """
        Permet de tuer l'agent
        """
        self.life = False

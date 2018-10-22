#coding: utf-8
from src.core.Agent import Agent

"""
Contient les caractéristiques des particules et une méthode decide(), destinée à coder le processus de décision de ces particules
"""
class Balle(Agent):

    def __init__(self, posX, posY, data):
        super(Balle, self).__init__(posX, posY)

        self.color = "grey"

        self.change = 0

    def swap_pas(self, agent):
        """
        Swap la direction de 2 agents
        """
        agent.pasX, agent.pasY, self.pasX, self.pasY = self.pasX, self.pasY, agent.pasX, agent.pasY
        self.color = "red"
        agent.color = "red"

        self.change = 1

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.change = 0
        newPosX = self.posX + (self.pasX) # nouveau posX
        newPosY = self.posY + (self.pasY) # nouveau posY

        env.setAgent(self, newPosX, newPosY)
        
    def getColor(self):
        """
        Retourne la couleur de l'agent

        :return: Couleur de l'agent
        """
        return self.color

    def getForm(self):
        """
        Retourne la forme de l'agent

        :return: Forme de l'agent
        """
        return "circle"
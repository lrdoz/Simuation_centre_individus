#coding: utf-8
from src.core.Agent import Agent

"""
Contient les caractéristiques des particules et une méthode decide(), destinée à coder le processus de décision de ces particules
"""
class WAgent(Agent):

    def __init__(self, posX, posY):
        super(WAgent, self).__init__(posX, posY)
        # position initiale de la particule

        self.age = 0
        self.gestation = 0

        self.form = "rectangle"

    def getAge(self):
        """
        """
        return self.age

    def updatePosition(self, env, newPos, classAgent, data):
        """
        Bouge l'agent dans une nouvelle case et enfante si besoin
        """
        if(self.isAlive()):
            self.change = True
            env.setAgentPosition(self, newPos[0], newPos[1])
            childPosX, childPosY = self.posX, self.posY
            self.posX, self.posY = newPos

            #On créait le nouveau poisson
            if(self.gestation >= self.gestationDay):
                self.gestation = 0
                child = classAgent(childPosX, childPosY, data)
                env.appendAgent(child, childPosX, childPosY)

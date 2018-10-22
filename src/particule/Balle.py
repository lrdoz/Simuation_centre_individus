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

        self.torus = data[0]

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

        newPos = self.correctPosition(env.l, env.h, newPosX, newPosY)

        maybeAgent = self.getPositionAgent(newPos[0], newPos[1]) 

        if maybeAgent == None:
            env.setAgentPosition(self, newPos[0], newPos[1])
        
        else:
            agent.swap_pas(maybeAgent)
            newPosX = agent.posX + agent.pasX # nouveau posX
            newPosY = agent.posY + agent.pasY # nouveau posY


            newPos = self.correctPosition(env.l, env.h, newPosX, newPosY)
            if (self.t):
                newPosX = (newPosX+self.l)%self.l
                newPosY = (newPosY+self.h)%self.h
            else :
                if (newPosX < 0): # on replace correctement la boule si besoin
                    newPosX += 2
                    agent.pasX *= -1
                if ((self.l - newPosX) <= 1):
                    newPosX -= 2
                    agent.pasX *= -1
                if (newPosY < 0):
                    newPosY += 2
                    agent.pasY *= -1
                if ((self.h - newPosY) <= 1):
                    newPosY -= 2
                    agent.pasY *= -1
        
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

    def correctPosition(self, l, h, newPosX, newPosY):
        if (self.torus): # si le monde est torique
            newPosX = (newPosX+ l)% l
            newPosY = (newPosY+ h)% h

        else : # sinon
            if (posX < 0): # on replace correctement la boule si besoin
                newPosX += 2
                agent.pasX *= -1
            if ((l - posX) < 1):
                newPosX -= 2
                agent.pasX *= -1
            if (posY < 0):
                newPosY += 2
                agent.pasY *= -1
            if ((h - posY) < 1):
                newPosY -= 2
                agent.pasY *= -1

        return newPosX, newPosY
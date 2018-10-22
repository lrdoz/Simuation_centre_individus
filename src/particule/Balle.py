#coding: utf-8
from src.core.Agent import Agent
import random

"""
Contient les caractéristiques des particules et une méthode decide(), destinée à coder le processus de décision de ces particules
"""
class Balle(Agent):

    def __init__(self, posX, posY, data):
        super(Balle, self).__init__(posX, posY)

        self.color = "grey"

        self.pasX = random.randint(-1,1)
        self.pasY = random.randint(-1,1)

        self.torus = data[0]

    def swap_pas(self, agent):
        """
        Swap la direction de 2 agents
        """
        agent.pasX, agent.pasY, self.pasX, self.pasY = self.pasX, self.pasY, agent.pasX, agent.pasY
        self.color = "red"
        agent.color = "red"


    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.change = False

        # on fait bouger l'agent
        newPosX = self.posX + (self.pasX) # nouveau posX
        newPosY = self.posY + (self.pasY) # nouveau posY

        # renvoie la bonne position par rapport à l'environnement
        newPosX, newPosY = self.correctPosition(env.l, env.h, newPosX, newPosY)

        # vérifie qu'il n'y ait pas d'agent
        maybeAgent = env.getPositionAgent(newPosX, newPosY)

        if maybeAgent == None: # si pas de balle à la nouvelle position, il y va
            self.change = True
            env.setAgentPosition(self, newPosX, newPosY)
            self.setPosition(newPosX, newPosY)

        else: # sinon, échange de valeur
            self.swap_pas(maybeAgent)

            newPosX = self.posX + self.pasX # nouveau posX
            newPosY = self.posY + self.pasY # nouveau posY

            newPosX, newPosY = self.correctPosition(env.l, env.h, newPosX, newPosY)

            self.change = True
            env.setAgentPosition(self, newPosX, newPosY)
            self.setPosition(newPosX, newPosY)

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
        """
        Renvoie la position après avoir avancé, dépend de l'environnement, si le monde est torique ou non
        """
        if (self.torus): # si le monde est torique
            newPosX = (newPosX+ l)% l
            newPosY = (newPosY+ h)% h

        else : # sinon
            if (newPosX < 0): # on replace correctement la boule si besoin
                newPosX += 2
                self.pasX *= -1
            if ((l - newPosX) < 1):
                newPosX -= 2
                self.pasX *= -1
            if (newPosY < 0):
                newPosY += 2
                self.pasY *= -1
            if ((h - newPosY) < 1):
                newPosY -= 2
                self.pasY *= -1

        return newPosX, newPosY

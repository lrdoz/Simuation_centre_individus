#coding: utf-8

"""
Contient les caractéristiques de base d'un agent
"""
class Agent:

    def __init__(self, posX, posY):
        """
        """
        # position initiale de la particule
        self.posX = posX
        self.posY = posY
        self.life = True
        self.time = 0
        self.change = False
        self.fearMode = False

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        raise NotImplementedError( "Should have implemented this" )

    def setPosition(self, posX, posY):
        """
        Méthode pour set la nouvelle position de l'agent
        """
        self.posX = posX
        self.posY = posY

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        raise NotImplementedError( "Should have implemented this" )

    def getColor(self):
        """
        Retourne la couleur de l'agent

        :return: Couleur de l'agent
        """
        raise NotImplementedError( "Should have implemented this" )

    def getForm(self):
        """
        Retourne la forme de l'agent

        :return: Forme de l'agent
        """
        raise NotImplementedError( "Should have implemented this" )

    def dead(self):
        """
        Permet de tuer l'agent
        """
        self.life = False

    def isAlive(self):
        """
        Permet de savoir si l'agent est en vie

        :return: Etat de l'agent
        """
        return self.life

    def on_press(self, key):
        """
        Définit le comportement lorsqu'un evenement du clavier est envoyé

        :param key: Evenement du clavier
        """
        pass

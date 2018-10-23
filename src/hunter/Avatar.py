from src.core.Agent import Agent
from pynput import keyboard

"""
Implémentation d'un agent pouvant être manipuler par un individue
"""
class Avatar(Agent):
    def __init__(self, posX, posY, data):
        # position initiale de l'avatar
        super(Avatar, self).__init__(posX, posY)

        self.vector = (0,1)
        self.form = "circle"
        self.delay = data[0]
        self.color = "yellow"

    def decide(self, env):
        """
        Méthode qui permet à un agent de décider de son comportement

        :param env: Environement de l'agent
        """
        self.time += 1

        if self.delay <= self.time:
            self.time = 0
            xp, yp = (self.posX+self.vector[0]+env.l) % env.l, (self.posY+self.vector[1]+env.h) % env.h # met à jour la position

            env.updateValues(self.posX, self.posY)

            case = env.getPositionAgent(xp, yp)

            if (case == None): # regarde si il peut bouger
                env.setAgentPosition(self, xp, yp)
                self.posX, self.posY = xp, yp
                env.updateValues(xp, yp)

            elif case.getType() == 3:
                env.kill(xp, yp)

                env.setAgentPosition(self, xp, yp)
                self.posX, self.posY = xp, yp
                env.updateValues(xp, yp)

    def getColor(self):
        """
        Retourne la couleur de l'agent

        :return: Couleur de l'agent
        """
        return "yellow"

    def on_press(self, key):

        #On change le vector du pac man
        try:
            if key == keyboard.Key.down: #down
                self.vector = (0, 1)
            elif key == keyboard.Key.up: #up
                self.vector = (0, -1)
            elif key == keyboard.Key.left: #left
                self.vector = (-1, 0)
            elif key == keyboard.Key.right: #right
                self.vector = (1, 0)
            elif key == keyboard.KeyCode.from_char('o'):
                if self.delay > 0:
                    self.delay -=1
            elif key == keyboard.KeyCode.from_char('p'):
                self.delay += 1

        except AttributeError:
            print('special key {0} pressed'.format(
                key))

    def getType(self):
        """
        Retourne le type de l'agent

        :return: Retourne le type de l'agent
        """
        return 0

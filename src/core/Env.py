
import random
import numpy as np

# LISTE INITIALISEE UNE FOIS POUR LES POSTIONS ET LES POISSONS


"""
Environnement sous forme de grille 2D (coordonnées entières et environnement discret)
où sont placés les particules.
Celui-ci peut-être torique ou non
"""

class Env:
    def __init__(self, l, h, size, vector):
        self.l = l
        self.h = h
        self.grid = []
        self.l_agents =[]
        self.size = size

        #Initialisation de la grille
        self.grid = [[(None, -1)] * (self.h) for _ in range(self.l)]

    #############################################
    #   Opération primitive sur l'environement  #
    #############################################

    def vonNeumman(self):
        """
        4 voisins
        """
        return self.vectorPosition([(0,-1), (1,0), (0,1), (-1,0)])

    def moore(self):
        """
        8 voisins
        """
        return self.vectorPosition([(-1,-1), (-1, 1), (1, -1), (1, 1), (0,-1), (1,0), (0,1), (-1,0)])

    def vectorPosition(self, vector):
        """
        Permet de récupère toutes les positions du vecteur

        :param vector: list des vecteurs regarder
        :return: list des case sur la grille
        """
        res =[]
        #On parcours toutes les case adjacent
        for dx, dy in vector:
            xp, yp = (x+dx+self.l) % self.l, (y+dy+self.h) % self.h
            case = self.getPosition(xp, yp)

            res += [((xp, yp),case[0], case[1])]
        random.shuffle(res)

        return res

    def getPosition(self, posX, posY):
        """
        Retourne ce qu'il y a à la position x,y

        :param posX: Position x de l'agent
        :param posY: Position y de l'agent
        """
        return self.grid[posX][posY]

    def setPosition(self, agent, posX, posY):
        """
        Set un agent à la position x, y sur la grille

        :param posX: Position x de l'agent
        :param posY: Position y de l'agent
        """
        self.grid[posX][posY]=(agent, self.grid[posX][posY][1])

    def setValue(self, posX, posY, value):
        """
        Définit la valeur de la case posX, posY

        :param posX: Position x de la valeur
        :param posY: Position y de la valeur
        """
        self.grid[posX][posY] = (self.grid[posX][posY][0], value)

    def unsetAgent(self, posX, posY):
        """
        Supprime l'agent de la grille qui se trouve à la position posX, posY

        :param posX: Position x de l'agent
        :param posY: Position y de l'agent
        """
        v =self.grid[posX][posY][1]
        self.grid[posX][posY]=(None, v)

    def getValue(self, posX, posY):
        """
        Retourne la valeur de la case posX, posY

        :param posX: Position x de la valeur
        :param posY: Position y de la valeur
        :return: Valeur de la case posX, posY
        """
        return self.grid[posX][posY][1]

    def getPositionAgent (self, posX, posY):
        """
        Retourne l'agent à la position posX, posY

        :param posX: Position x de l'agent
        :param posY: Position y de l'agent
        :return: Agent à la position posX, posY
        """
        return self.grid[posX][posY][0]

    ##########################################
    #   Opération primitive sur les agents  #
    #########################################

    def kill(self, posX, posY):
        """
        Tue l'agent à la case posX, posY

        :param posX: Position x de l'agent
        :param posY: Position y de l'agent
        """
        toRm = self.getPosition(posX, posY)[0]
        if (toRm != None):
            self.unsetAgent(posX, posY)
            toRm.dead()

    def removeDeadAgent(self):
        """
        Permet de supprimer tous les agents morts

        :return: List des agents morts
        """
        agents = []
        dead = []
        size = len(self.l_agents)

        for agent  in self.l_agents:
            if agent.isAlive():
                agents.append(agent)
            else:
                dead.append(agent)
        self.l_agents = agents

        return dead

    def generate(self, n, classAgent, data=[]):
        """
        Place n agent(s) aléatoirement sur la grille

        :param n: Number agent generate
        :param classAgent: Class de l'agent créer
        """
        i = 0

        while (i < n) : # on génère les n agents dans le tableau

            # pour chaque agent, on le place aléatoirement sur la map
            posX = random.randint(0, self.l-1)
            posY = random.randint(0, self.h-1)
            if (self.getPosition(posX, posY)[0] == None): # si pas d'agent
                agent = classAgent(posX, posY, data)
                self.setAgentPosition(agent, posX, posY)
                self.l_agents.append(agent)
                i += 1

    def generate2(self, grille, classAgent, data=[]):
        """
        Place des agents sur la liste des positions
        """
        for i in range(0, self.l):
            for j in range(0, self.h):
                if (not (grille[i][j])):
                    agent = classAgent(i, j, data)
                    self.setAgentPosition(agent, i, j)
                    self.l_agents.append(agent)

    def setAgentPosition(self, agent, posX, posY):
        """
        Set un agent à la position x, y sur la grille
        """
        self.unsetAgent(agent.posX, agent.posY)

        self.setPosition(agent, posX, posY)

    def resetValue(self):
        """
        Set toutes les valeurs de la grille à -1
        """
        for x in range(0, self.l, 1):
            for y in range(0, self.h, 1):
                self.grid[x][y] = (self.grid[x][y][0], -1)

    def updateValues(self, x, y):
        """
        Par rapport à des coordonnées, déploie l'algorithme de Algo de Dijkstra,
        càd donne une valeur à chaque case de la grille suivant sa proximité avec la cible en posX,posY
        """
        self.resetValue() #reset des valeurs
        fil = list() # file pour les cases
        count  = 0 # valeur à mettre sur la case

        self.grid[x][y]=(self.grid[x][y][0],0)
        for vector in self.vector:
            xp, yp = (x+vector[0]+self.l) % self.l, (y+vector[1]+self.h) % self.h
            fil.append((xp, yp))

        while fil : # tant qu'il y a des cases à compléter
            #Compteur du parcours
            count +=1
            #Prochaine position à mettre à jour
            newFil = list()

            #On parcours les positions à mettre à jour
            for pos in fil:
                case = self.getPosition(pos[0], pos[1])
                if(case[1] == -1 and (case[0] == None or case[0].getType() != 1)):
                    self.setValue(pos[0], pos[1], count)

                    #On définit les voisins
                    for vector in self.vector:
                        xp, yp = (pos[0]+vector[0]+self.l) % self.l, (pos[1]+vector[1]+self.h) % self.h
                        newFil.append((xp, yp))

            fil = newFil
        return

    def near(self, x, y):
        """
        Regarde les case autour de l'agent et prend une case disponible
        """
        self.cptPos = 0
        res =[]
        #On parcours toutes les case adjacent
        for dx, dy in self.vector:
            xp, yp = (x+dx+self.l) % self.l, (y+dy+self.h) % self.h
            case = self.getPosition(xp, yp)

            # if (case[1] != -1):
            res += [((xp, yp),case[0], case[1])]
        random.shuffle(res)
        return res

    def canMove(self, x, y):
        """

        """
        return (self.getPosition(x,y)[0] == None)

    def appendAgent(self, agent, posX, posY):
        """
        Ajout un agent
        """
        self.setAgentPosition(agent, posX, posY)
        self.l_agents.append(agent)


    #########
    # DEBUG #
    #########

    def printGrid(self):
        nbAgent =0
        val =[]
        for y in range(self.h):
            line = ""
            lineVal = ""
            for x in range(self.l):
                if self.grid[x][y][0] == None:
                    lineVal += str(self.grid[x][y][1])+"| "
                    line += "V| "
                elif self.grid[x][y][0].getColor() == "black":
                    line += "M| "
                    lineVal += "M| "
                else:
                    nbAgent +=1
                    line += "A| "
                    lineVal += str(self.grid[x][y][1])+"| "
            val += [lineVal]
            print(line)
        print()
        for tmp in val:
            print(tmp)
        print("Nb agents :")
        print()

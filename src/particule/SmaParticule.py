#coding: utf-8
from src.core.Env import Env
from src.core.View import View
from src.particule.Balle import Balle
from tkinter import *
import random
import time
import json
from pprint import pprint

"""
Contient la méthode run() qui effectue le tour de parole
"""
class SMA:

    def __init__(self, n, l, h, t, size, limite, refresh, delay, time, action, trace, grid):

        #env
        self.env = Env(l, h)

        #n
        self.n = n

        #liste des agents
        self.env.generate(n, Balle, [t]) # liste des agents

        self.view = View(l, h, size, self.env.l_agents)

        if(grid):
            self.view.create_grid()

        #nb de tours
        self.nturn = 0
        self.limite = limite

        #refresh
        self.refresh = refresh

        #delay
        self.delay = delay

        # time
        self.time = time

        # scheduling
        self.action = action

        self.trace = trace

        self.order = range(n)

    def scheduling(self):
        """
        Mélange la liste d'ordre
        """
        if (self.action == 2):
            self.order = random.sample(range(self.n), k=self.n)
        if (self.action == 3):
            self.order = [random.randint(0,self.n-1) for _ in range(self.n)]

    def turn(self):
        """
        Déroulement d'un tour
        """
        if (self.nturn == self.limite): # nb de tours < limite ?
            exit()

        self.nturn+=1 # on incrémente le nombre de tour
        self.scheduling() #quelle méthode pour donner la parole ?

        # taux de refresh de la page
        for i in range(0,self.refresh):
            # TOUR DE TOUS LES AGENTS
            for ag in self.order:
                self.env.l_agents[ag].decide(self.env)
                if (self.trace):
                    self.n_rebond += self.env.l_agents[ag].rebond
                    self.t_rebond += self.env.l_agents[ag].rebond
                    # self.env.l_agents[ag].toPrint()

        if (self.delay): # ajoute un delay
            self.time+= 1

        if (self.trace):
            print ("{} {}".format(self.nturn, self.n_rebond))
            self.n_rebond = 0
        self.view.set_agent(self.time, self.env.l_agents, self.turn)


    def run(self):
        """
        """
        if self.trace :
            self.n_rebond = 0
            self.t_rebond = 0
        self.view.set_agent(self.time, self.env.l_agents, self.turn)
        self.view.mainloop()

def parse():
    """
    Parse le fichier JSON de config
    """
    with open('src/particule/Properties.json') as data_file:
        data = json.load(data_file)
        return data

def main():
    data = parse()

    # set des valeurs par défault
    n = 10
    l = 100
    h = 100
    t = False
    size = 10
    action = 2
    limite = -1
    refresh = 1
    delay = False
    time = 20
    trace = False
    grid = False

    # parcours des options saisis par l'utilisateur
    if (data["torus"]):
        t = True
    if (data["gridSizeX"]):
        l = int(data["gridSizeX"])
    if (data["gridSizeY"]):
        h = int(data["gridSizeY"])
    if (data["boxSize"]):
        size = int(data["boxSize"])
    if (data["delay"]):
        delay = True
    if (data["scheduling"]):
        action = int(data["scheduling"])
    if (data["trace"]):
        trace = True
    if (data["nbTicks"]):
        limite = int(data["nbTicks"])
    if (data["seed"]):
        random.seed(seed)
    if (data["refresh"]):
        refresh = int(data["refresh"])
    if (data["nbParticles"]):
        n = int(data["nbParticles"])
    if (data["time"]):
        speed = int(data["time"])
    if (data["grid"]):
        grid = True

    game = SMA(n, l, h, t, size, limite, refresh, delay, speed, action, trace, grid)
    game.run()

    # except :
    #     print("Tu chies dans la colle quelque part Célestine ")


if __name__ == "__main__":
    # execute only if run as a script
    main()

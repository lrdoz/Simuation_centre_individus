from tkinter import *

"""
Définit la view de l'environement
"""
class View :
    def __init__(self, l, h, size, l_agents):

        self.w = l*(size+1)
        self.h = h*(size+1)
        self.size = size

        #vue
        self.window = Tk()
        self.window.geometry(str(self.w)+"x"+str(self.h))

        #canvas
        self.canvas = Canvas(self.window, height=self.h, width=self.w,background='white')
        self.canvas.grid(row=1, column=1, sticky='w')
        self.canvas
        self.grid = 0


    def create_grid(self, event=None):
        """
        Crée les lignes de la grille
        """
        # Creates all vertical lines at intevals of 100
        for i in range(0, self.w, self.size+1):
            self.canvas.create_line([(i, 0), (i, self.h)], tag='grid_line', fill='white')

        # Creates all horizontal lines at intevals of 100
        for i in range(0, self.h, self.size+1):
            self.canvas.create_line([(0, i), (self.w, i)], tag='grid_line', fill='white')

    def set_agent(self, time, l_agents, fct):
        """
        Bouge les ronds des agents
        """
        for agent in l_agents:
            x = agent.posX
            y = agent.posY
            isInit = self.isCanvasInit(agent)

            if not agent.isAlive() :
                if isInit :
                    self.canvas.delete(agent.circle)
            else:
                if (isInit):
                    self.canvas.coords(agent.circle, (x * self.size)+x + self.grid,
                                                        (y * self.size)+ y+ self.grid,
                                                        (x * self.size) + self.size + x - self.grid,
                                                        (y * self.size) + self.size + y - self.grid)
                else:
                    color = agent.getColor()
                    if (agent.getForm() == "circle"):
                        agent.circle = self.canvas.create_oval([(x * self.size)+x+ self.grid,
                                                            (y * self.size)+ y+ self.grid,
                                                            (x * self.size) + self.size + x - self.grid,
                                                            (y * self.size) + self.size + y - self.grid],
                                                            outline=color, fill=color)
                    else :
                        agent.circle = self.canvas.create_rectangle([(x * self.size)+x+ self.grid,
                                                            (y * self.size)+ y+ self.grid,
                                                            (x * self.size) + self.size + x - self.grid,
                                                            (y * self.size) + self.size + y - self.grid],
                                                            outline=color, fill=color)
        self.window.after(time, fct)

    def isCanvasInit(self, agent):
        """

        """
        try:
            agent.circle
            return True
        except:
            return False

    def mainloop(self):
        """
        """
        self.window.mainloop()

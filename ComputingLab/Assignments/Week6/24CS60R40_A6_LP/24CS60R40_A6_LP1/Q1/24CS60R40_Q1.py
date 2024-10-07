

from ortools.linear_solver import pywraplp

def SolveNutritionPlan(A, B):
  
    solver = pywraplp.Solver.CreateSolver('GLOP')
    if not solver:
        print("Could not create the solver.")
        return None, None

   
    food_items = ['Chicken', 'Rice', 'Broccoli', 'Salmon', 'Quinoa']
    cost = [5, 2, 1, 8, 4]
    calories = [250, 200, 50, 300, 220]
    protein = [30, 5, 4, 25, 8]
    carbohydrates = [0, 45, 10, 0, 39]
    fat = [10, 1, 0.5, 20, 4]
    

    x = {}
    for i in range(len(food_items)):
        x[i] = solver.NumVar(0, solver.infinity(), f'x_{i}')
    
   
    objective = solver.Objective()
    for i in range(len(food_items)):
        objective.SetCoefficient(x[i], cost[i])
    objective.SetMinimization()


    CalorieExp = solver.Sum(calories[i] * x[i] for i in range(len(food_items)))
    solver.Add(CalorieExp >= A)


    ProteinExp = solver.Sum(protein[i] * x[i] for i in range(len(food_items)))
    solver.Add(ProteinExp >= B)
  
    CarbExp = solver.Sum(carbohydrates[i] * x[i] for i in range(len(food_items)))
    solver.Add(CarbExp >= 150)

  
    FatExp = solver.Sum(fat[i] * x[i] for i in range(len(food_items)))
    solver.Add(FatExp >= 40)

   
    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        cost = objective.Value()
        quantities = [x[i].solution_value() for i in range(len(food_items))]
        return cost, quantities
    else:
        return None, None


with open('input.txt', 'r') as file:
    A = int(file.readline().strip())
    B = int(file.readline().strip())
    

cost, quantities = SolveNutritionPlan(A, B)

if cost is not None:
    with open('output.txt', 'w') as file:
        file.write(f"{cost:.2f}\n")

        for quantity in quantities:
            file.write(f"{quantity:.2f}\n")
else:
    with open('output.txt', 'w') as file:
        file.write("No solution exists.\n")



from ortools.linear_solver import pywraplp

def create_data_model():
    """Create the data for the problem."""
    data = {}
    data['products'] = ['A', 'B', 'C', 'D']
    data['factories'] = [1, 2, 3]
    
    data['price'] = {'A': 100, 'B': 120, 'C': 80, 'D': 150}
    
    data['cost'] = {
        ('A', 1): 60, ('A', 2): 65, ('A', 3): 55,
        ('B', 1): 70, ('B', 2): 75, ('B', 3): 80,
        ('C', 1): 40, ('C', 2): 45, ('C', 3): 50,
        ('D', 1): 90, ('D', 2): 100, ('D', 3): 95
    }
    
    data['raw_material'] = {'A': 2, 'B': 3, 'C': 1.5, 'D': 4}
    data['labor_hours'] = {'A': 3, 'B': 4, 'C': 2, 'D': 5}
    data['co2_emissions'] = {'A': 5, 'B': 7, 'C': 3, 'D': 8}
    
    data['total_raw_material'] = 5000
    data['labor_hours_per_factory'] = 800
    data['production_capacity_per_factory'] = 1000
    data['min_production_per_product'] = 100
    data['max_storage_per_product'] = 2000
    data['max_co2_emissions'] = 10000
    data['max_production_budget'] = 500000
    
    data['market_demand'] = {'A': 1500, 'B': 1200, 'C': 1800, 'D': 1000}
    
    return data

def GlobtechManufacturingSolution(data):
    
    solver = pywraplp.Solver.CreateSolver('GLOP')

    if not solver:
        print("Problem to create solver variable")
        return

    x = {}
    for i in data['products']:
        for j in data['factories']:
            x[(i, j)] = solver.NumVar(0, solver.infinity(), f'x_{i}_{j}')
    

    objective = solver.Objective()
    for i in data['products']:
        for j in data['factories']:
            objective.SetCoefficient(x[(i, j)], data['price'][i] - data['cost'][(i, j)])
    objective.SetMaximization()

    RawMaterialExp = solver.Sum(data['raw_material'][i] * x[(i, j)] for i in data['products'] for j in data['factories'])
    solver.Add(RawMaterialExp <= data['total_raw_material'])


    for j in data['factories']:
        LaborHoursExp = solver.Sum(data['labor_hours'][i] * x[(i, j)] for i in data['products'])
        solver.Add(LaborHoursExp <= data['labor_hours_per_factory'])


    for j in data['factories']:
        CapacityExp = solver.Sum(x[(i, j)] for i in data['products'])
        solver.Add(CapacityExp <= data['production_capacity_per_factory'])


    for i in data['products']:
        MinProductionExp = solver.Sum(x[(i, j)] for j in data['factories'])
        solver.Add(MinProductionExp >= data['min_production_per_product'])


    for i in data['products']:
        DemandExp = solver.Sum(x[(i, j)] for j in data['factories'])
        solver.Add(DemandExp <= data['market_demand'][i])


    Co2EmissionsExp = solver.Sum(data['co2_emissions'][i] * x[(i, j)] for i in data['products'] for j in data['factories'])
    solver.Add(Co2EmissionsExp <= data['max_co2_emissions'])

    BudgetExpr = solver.Sum(data['cost'][(i, j)] * x[(i, j)] for i in data['products'] for j in data['factories'])
    solver.Add(BudgetExpr <= data['max_production_budget'])

    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        with open('output.txt', 'w') as f:
            
            for i in data['products']:
                for j in data['factories']:
                    f.write(f"{int(x[(i, j)].solution_value())}\n")
            
            total_raw_material = sum(data['raw_material'][i] * x[(i, j)].solution_value()
                                     for i in data['products'] for j in data['factories'])
            f.write(f"{int(total_raw_material)} / {data['total_raw_material']}\n")
            
            total_labor_hours = sum(data['labor_hours'][i] * x[(i, j)].solution_value()
                                    for i in data['products'] for j in data['factories'])
            f.write(f"{int(total_labor_hours)} / {data['labor_hours_per_factory'] * len(data['factories'])}\n")
            
            total_co2_emissions = sum(data['co2_emissions'][i] * x[(i, j)].solution_value()
                                      for i in data['products'] for j in data['factories'])
            f.write(f"{int(total_co2_emissions)} / {data['max_co2_emissions']}\n")
            
            total_production_cost = sum(data['cost'][(i, j)] * x[(i, j)].solution_value()
                                        for i in data['products'] for j in data['factories'])
            f.write(f"{int(total_production_cost)} / {data['max_production_budget']}\n")
    else:
        print("The problem does not have an optimal solution.")

data = create_data_model()

GlobtechManufacturingSolution(data)

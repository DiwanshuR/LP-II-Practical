import heapq
def a_star(grid, start, goal):
    def heuristic(a,b):
        return abs(a[0] - b[0]) + abs(a[1] - b[1])
    
    rows, cols = len(grid), len(grid[0])
    open_heap = []  # priority queue of (f, g, cell)
    heapq.heappush(open_heap, (heuristic(start, goal), 0, start))  #konse heap pe daal rahe ho, f = h(start, goal), g = 0, cell = start
    came_from = {}  # for path reconstruction
    g_score = {start: 0}
    closed = set()  # closed set of cells
    
    #MAIN LOOP runs till open_heap becomes empty
    # open_heap is first popped but then pushed at last so when there is a path it not becomes empty if it becomes empty then there is no path so return []
    
    while open_heap:
        f,g,current = heapq.heappop(open_heap)  # pop the cell with lowest f value  priority queue so top is minimmum only
        if current == goal:
            #target is reached form path
            path = []
            while current:
                path.append(current)
                current = came_from.get(current)  # get the parent of current cell
                
            return path[::-1]  #we are taking from last to first so we need to reverse the path
        
        # check if current cell is already in closed set
        if current in closed:
            continue
        
        # add curr to closed set
        closed.add(current)
        
        # check neighbours in all 4 directions
        for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
            neighbour = (current[0] + dr, current[1] + dc)  # get the neighbour cell
            r,c = neighbour
            
            # check if neighbour is within the boundary
            if not( 0 <= r < rows and 0 <= c < cols):
                continue
            
            #check if it is a wall
            if grid[r][c] == 1:
                continue
            
            # means it is a free cell so go forward and find g
            tentative_g = g + 1
            
            if tentative_g < g_score.get(neighbour, float('inf')):
                came_from[neighbour] = current
                g_score[neighbour] = tentative_g  # update g score of neighbour cell
                f_score = tentative_g + heuristic(neighbour, goal)   # f=g+h
                
                # push nbr cell to open heap
                heapq.heappush(open_heap, (f_score, tentative_g, neighbour)) #(f,g,cell)
            
        
    return []




if __name__ == "__main__":
    maze = [
        [0,0,0,0,1],
        [1,1,0,1,0],
        [0,0,0,0,0],
        [0,1,1,1,0],
        [0,0,0,1,0],
    ]
    start = (0,0)
    goal = (4,4)
    path = a_star(maze, start, goal)
    print("Path from start to goal:", path)
    
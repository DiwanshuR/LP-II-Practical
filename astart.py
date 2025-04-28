import heapq

def a_star(grid, start, goal):
    """
    grid: 2D list of 0 (free) / 1 (wall)
    start, goal: (row, col) tuples
    returns: list of cells from start to goal (inclusive) or [] if no path
    """
    def heuristic(a, b):
        # Manhattan distance
        return abs(a[0] - b[0]) + abs(a[1] - b[1])

    rows, cols = len(grid), len(grid[0])
    open_heap = []  # priority queue of (f, g, cell)
    heapq.heappush(open_heap, (heuristic(start, goal), 0, start))
    came_from = {}  # for path reconstruction
    g_score = {start: 0}
    closed = set()

    while open_heap:
        f, g, current = heapq.heappop(open_heap)
        if current == goal:
            # reconstruct path
            path = []
            while current:
                path.append(current)
                current = came_from.get(current)
            return path[::-1]

        if current in closed:
            continue
        closed.add(current)

        for dr, dc in [(1,0),(-1,0),(0,1),(0,-1)]:
            neighbor = (current[0]+dr, current[1]+dc)
            r, c = neighbor
            if not (0 <= r < rows and 0 <= c < cols): 
                continue
            if grid[r][c] == 1: 
                continue

            tentative_g = g + 1
            if tentative_g < g_score.get(neighbor, float('inf')):
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g
                f_score = tentative_g + heuristic(neighbor, goal)
                heapq.heappush(open_heap, (f_score, tentative_g, neighbor))

    return []  # no path found

# Example usage:
if __name__ == "__main__":
    maze = [
        [0,0,0,0,1],
        [1,1,0,1,0],
        [0,0,0,0,0],
        [0,1,1,1,0],
        [0,0,0,1,0],
    ]
    start = (0,0)
    goal  = (4,4)
    path = a_star(maze, start, goal)
    print("Path:", path)

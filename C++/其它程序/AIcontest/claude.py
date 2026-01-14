def solve():
    t = int(input())
    
    for _ in range(t):
        n = int(input())
        s = input().strip()
        
        # Identify groups of consecutive 0s and 1s
        groups = []
        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            groups.append((s[i], i, j - 1))  # (type, start, end)
            i = j
        
        # Check for impossible case: single '0' between two '1' groups
        for i in range(len(groups)):
            if groups[i][0] == '0':  # Unstable group
                length = groups[i][2] - groups[i][1] + 1
                if length == 1:  # Single unstable position
                    # Check if it's between two stable groups
                    if i > 0 and i < len(groups) - 1:
                        if groups[i-1][0] == '1' and groups[i+1][0] == '1':
                            print("NO")
                            break
        else:
            # No impossible case found, construct permutation
            p = list(range(1, n + 1))  # Start with identity [1, 2, ..., n]
            
            # Process each unstable group
            for group_type, start, end in groups:
                if group_type == '0':  # Unstable group
                    length = end - start + 1
                    
                    if length == 1:
                        # Single unstable at boundary
                        # Already handled in impossible check
                        # For boundary cases, swap with neighbor
                        if start == 0 and n > 1:
                            p[0], p[1] = p[1], p[0]
                        elif end == n - 1 and n > 1:
                            p[n-1], p[n-2] = p[n-2], p[n-1]
                    elif length == 2:
                        # Swap the pair
                        p[start], p[start + 1] = p[start + 1], p[start]
                    else:
                        # For larger groups, use a simple derangement
                        # Rotate left by 1: [a, b, c, d] -> [b, c, d, a]
                        temp = p[start:end + 1]
                        for i in range(length):
                            p[start + i] = temp[(i + 1) % length]
            
            print("YES")
            print(*p)

solve()
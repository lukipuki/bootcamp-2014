//924
import java.util.*;

public class maze {
    static int rows, cols;
    static boolean obs[][];
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nt = input.nextInt();
        for (int t = 0; t < nt; t++) {
            rows = input.nextInt();
            cols = input.nextInt();
            obs = new boolean[rows][cols];
            int startr = 0, startc = 0, goalr = 0, goalc = 0;
            for (int r = 0; r < rows; r++) {
                String line = input.next();
                for (int c = 0; c < cols; c++)
                    switch (line.charAt(c)) {
                    case '.':
                        break;
                    case 'D':
                        goalr = r; goalc = c; break;
                    case 'R':
                        startr = r; startc = c; break;
                    case 'B':
                        obs[r][c] = true;
                    }
            }
            state init = new state(startr, startc, -1, -1);
            HashMap<state,state> visited = new HashMap<state,state>();
            LinkedList<state> q = new LinkedList<state>();
            q.add(init);
            visited.put(init,null);
            boolean found = false;
            while (!q.isEmpty()) {
                state curr = q.pop();
                if (curr.r == goalr && curr.c == goalc) {
                    System.out.println(count(curr,visited));
                    found = true;
                    break;
                }
                LinkedList<state> nexts = succ(curr);
                for (state ns : nexts) {
                    if (!visited.containsKey(ns)) {
                        visited.put(ns,curr);
                        q.add(ns);
                    }
                }
            }
            if (!found) System.out.println("-1");
        }

    }

    public static LinkedList<state> succ(state s) {
        LinkedList<state> ll = new LinkedList<state>();
        // 0 is r 1 is d 2 is l 3 is u
        for (int dir = 0; dir < 4; dir++) {
            if (dir == s.ld && dir == s.lld) continue;
            if (s.ld != -1 && Math.abs(dir-s.ld) == 2) continue;
            int nr = s.r, nc = s.c;
            switch(dir) {
            case 0:
                nc++; break;
            case 1:
                nr++; break;
            case 2:
                nc--; break;
            case 3:
                nr--; break;
            }
            if (nr < 0 || nr == rows || nc < 0 || nc == cols) continue;
            if (obs[nr][nc]) continue;
            ll.add(new state(nr,nc,dir,s.ld));
        }
        return ll;
    }

    public static int count(state last, HashMap<state,state> v) {
        int s = 0;
        state curr = last;
        while (curr != null) {
            curr = v.get(curr);
            if (curr != null) s++;
        }
        return s;
    }
}

class state {
    public int r, c, ld, lld;
    public state(int r, int c, int ld, int lld) {
        this.r = r; this.c = c; this.ld = ld; this.lld = lld;
    }
    public int hashCode() {
        return 1000000*r + 1000*c + 4*ld + lld;
    }
    public boolean equals(Object o) {
        state os = (state)(o);
        return (os.r == r && os.c == c && os.ld == ld && os.lld == lld);
    }
}

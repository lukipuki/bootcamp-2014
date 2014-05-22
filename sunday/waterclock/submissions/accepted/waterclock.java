import java.util.*;
public class waterclock {
    static HashSet<Span> tops, hightops;
    static int rows, cols, configs;
    static boolean[][] firstlw, firstbw;
    static int firstcount;

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        int nt = in.nextInt();
        for (int t = 0; t < nt; t++) {
            rows = in.nextInt();
            cols = in.nextInt();
            int entrycol = in.nextInt() - 1;
            int[][] tms = new int[rows][cols];
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    tms[r][c] = in.nextInt();
            boolean lw[][] = new boolean[rows][cols];
            boolean bw[][] = new boolean[rows][cols];
            // smaller than below needs wall
            for (int c = 0; c < cols; c++) {
                for (int r = 0; r < rows-1; r++)
                    if (tms[r+1][c] > tms[r][c])
                        bw[r][c] = true;
                // bottom of tank
                bw[rows-1][c] = true;
            }
            // different side by side needs wall
            for (int r = 0; r < rows; r++) {
                lw[r][0] = true;
                for (int c = 1; c < cols; c++) {
                    if (tms[r][c] != tms[r][c-1])
                        lw[r][c] = true;
                }
            }
            //            int[][] res = compute(lw,bw,entrycol);
            configs = 0; firstlw = null; firstbw = null;
            int[][] res = solve(lw,bw,tms,entrycol,0,0,false);
            printwalls(lw,bw);
            System.out.println();
            /*            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++)
                    System.out.print(res[r][c] + " ");
                System.out.println();
                }*/
        }
    }
    

    public static int countwalls(boolean[][] lw, boolean[][]bw) {
        int walls = 0;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                walls += (lw[r][c]?1:0) +(bw[r][c]?1:0);
        return walls;
    }

    public static void printwalls(boolean[][] lw, boolean[][]bw) {
        int walls = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++)
                walls += (lw[r][c]?1:0) +(bw[r][c]?1:0);
            for (int c = 0; c < cols; c++)
                // the cells
                System.out.print((lw[r][c]?"|":" ") + "o");
            System.out.println("|");
            for (int c = 0; c < cols; c++)
                System.out.print(" "+ (bw[r][c]?"-":" "));
            System.out.println();
        }
        //System.out.println(walls + " walls used");
    }

    public static boolean haszero(int[][] one) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (one[r][c] == 0) {
                    return true;
                }
        return false;
    }

    public static boolean isequal(int[][] one, int[][] two) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (one[r][c] != two[r][c])
                    return false;
        return true;
    }

    public static boolean samewalls(boolean[][] l1, boolean[][] l2, 
                                    boolean[][] b1, boolean[][] b2) { 
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (l1[r][c] != l2[r][c] || b1[r][c] != b2[r][c])
                    return false;
        return true;
    }
        
    public static int[][] solve(boolean[][] leftwall, boolean[][] botwall,
                                int[][] tms, int entrycol, int nextr, int nextc,
                                boolean doleft) {
        if (nextr == leftwall.length)
            return null;

        // configs++;
        //        System.out.println(nextr + "," + nextc + ": " + doleft + ": " + configs);
        
        //        printwalls(leftwall,botwall);
        int[][] comp = compute(leftwall,botwall,entrycol);
        if (isequal(tms,comp)) /* {
                                  checking for multiple solutions, there aren't any for our test cases.
            if (firstlw == null) {
                System.out.println("Sol:");
                printwalls(leftwall,botwall);
                System.out.println();
                firstcount = countwalls(leftwall, botwall);
                firstlw = new boolean[rows][cols];
                firstbw = new boolean[rows][cols];
                for (int r = 0; r < rows; r++)
                    for (int c = 0; c < cols; c++) {
                        firstlw[r][c] = leftwall[r][c];
                        firstbw[r][c] = botwall[r][c];
                    }
            } else if (countwalls(leftwall,botwall) <= firstcount) {
                if (!samewalls(firstlw, leftwall, firstbw, botwall)) {
                    System.out.println("Crap!!!");
                    printwalls(leftwall,botwall);
                }
            }
        }
          */  
            return tms;
        if (nextr == rows-1 && !doleft) 
            return null;
        if (haszero(comp))
            return null;
        // leftwall first, then botwall
        if (doleft) {
            // already true, skip along
            if (leftwall[nextr][nextc])
                if (nextc == cols-1)
                    return solve(leftwall,botwall,tms,entrycol,nextr,0,false);
                else
                    return solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,true);
            int[][] res = null;
            // let's try it as is, continue searching
            // at end of row, botwalls of this row next
            if (nextc == cols-1)
                res = solve(leftwall,botwall,tms,entrycol,nextr,0,false);
            else
                res = solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,true);
            // that didn't work, add a wall and carry on
            if (res == null) {
                /*if (nextr < 2)
                  System.out.println("adding left " + nextr + "," + nextc);*/
                leftwall[nextr][nextc] = true;
                if (nextc == cols-1)
                    res = solve(leftwall,botwall,tms,entrycol,nextr,0,false);
                else
                    res = solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,true);
                if (res == null)
                    leftwall[nextr][nextc] = false;
                return res;
            }
            return res;
        } else {// add botwalls
            // already true, skip along
            if (botwall[nextr][nextc])
                // end of row, go to next row and do lefts
                if (nextc == cols-1)
                    return solve(leftwall,botwall,tms,entrycol,nextr+1,0,true);
                else
                    return solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,false);
            int[][] res = null;
            // let's try it as is, continue searching
            if (nextc == cols-1)
                res = solve(leftwall,botwall,tms,entrycol,nextr+1,0,true);
            else
                res = solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,false);
            // that didn't work, add a wall and carry on
            if (res == null) {
                botwall[nextr][nextc] = true;
                if (nextc == cols-1)
                    res = solve(leftwall,botwall,tms,entrycol,nextr+1,0,true);
                else
                    res = solve(leftwall,botwall,tms,entrycol,nextr,nextc+1,false);
                if (res == null)
                    botwall[nextr][nextc] = false;
                return res;
            }
            return res;
        }
    }

    public static int[][] compute(boolean[][] leftwall, boolean[][] botwall,
                                  int entrycol) {
        tops = new HashSet<Span>();
        hightops = new HashSet<Span>();
        int[][] times = new int[rows][cols];
        int tm = 0;
        HashSet<Span> allsp = next(leftwall,botwall,times,0,entrycol);
        while (tm < rows*cols) {
            if (allsp.isEmpty())
                return times;
            for (Span sp : allsp)
                tm += sp.right-sp.left+1;
            for (Span sp : allsp) {
                //System.out.println(sp.row+" from "+sp.left+ " to "+sp.right+
                //                 " at " + tm);
                for (int c = sp.left; c <= sp.right; c++)
                    times[sp.row][c] = tm;
            }
            if (tm == rows*cols) break;
            Span curr = allsp.iterator().next();
            for (Iterator<Span> otit = tops.iterator(); otit.hasNext() ; ) { 
                Span ontop = otit.next();
                if (ontop.row == curr.row) {
                    allsp.add(ontop);
                    //tops.remove(otit);
                } else if (ontop.row < curr.row)
                    hightops.add(ontop);
            }
            allsp = upnext(leftwall,botwall,times,allsp);
        }
        return times;
    }

    public static HashSet<Span> upnext(boolean[][] lw, boolean[][] bw, 
                                       int[][] tms, HashSet<Span> from) {
        
        HashSet<Span> ups = new HashSet<Span>();
        HashSet<Span> newtops = new HashSet<Span>();
        HashSet<Span> downs = new HashSet<Span>();
        for (Span sp : from) {
            HashSet<Span> thisone = upnext(lw,bw,tms,sp);
            if (!thisone.isEmpty()) {
                Span first = thisone.iterator().next();
                if (first.row < sp.row) 
                    ups.addAll(thisone);
                else
                    downs.addAll(thisone);
            }
        }
        if (downs.isEmpty())
            return ups;
        return downs;
    }

    public static HashSet<Span> upnext(boolean[][] lw, boolean[][] bw, 
                                       int[][] tms, Span from) {
        //        System.out.println("up from "+from.row+" from "+from.left+ " to "+from.right);
        HashSet<Span> ret = new HashSet<Span>();
        if (from.row == 0) return ret;
        // what's available above?
        HashSet<Span> above = new HashSet<Span>();
        int r = from.row-1;
        int left = from.left;
        int right = from.right;
        while (left <= right) {
            int start = left;
            while (bw[r][start] && (start < right))
                start++;
            if (start == right && bw[r][start]) break;
            int end = start;
            while (!bw[r][end] && (end < right) && !lw[r][end+1])
                end++;
            //System.out.println("above " + r + " from " + start + " to " + end);
            above.add(new Span(r,start,end));
            left = end+1;
        }
        HashSet<Span> newtops = new HashSet<Span>();
        for (Span sp : above) {
            boolean spilt = false;
            // can spill left?
            while (!lw[sp.row][sp.left])  {
                sp.left--;
                if (!bw[sp.row][sp.left] && tms[sp.row+1][sp.left] == 0) {
                    //System.out.println("spill left");
                    ret.addAll(next(lw,bw,tms,sp.row,sp.left));
                    spilt = true;
                    break;
                }
            }
            // right
            while (sp.right < lw[0].length-1 && !lw[sp.row][sp.right+1])  {
                sp.right++;
                if (!bw[sp.row][sp.right] && tms[sp.row+1][sp.right] == 0) {
                    //System.out.println("spill right");
                    ret.addAll(next(lw,bw,tms,sp.row,sp.right));
                    spilt = true;
                    break;
                }
            }
            // didn't spill over, maybe we'll need to fill it later
            if (!spilt) {
                Span below = new Span(sp.row+1,sp.left,sp.right);
                newtops.add(below);
            }
        }
        //        System.out.println("above " + above.size() + " ret " + ret.size() + 
        //                           "newtops " + newtops.size());
        tops.clear();
        tops.addAll(newtops);
        tops.addAll(hightops);
        if (ret.isEmpty())
            return above;
        //System.out.println("saving " + newtops.size());
        //tops.addAll(newtops);
        return ret;
    }

    public static HashSet<Span> next(boolean[][] lw, boolean[][] bw, int[][] tms, 
                                     int r, int c) {
        HashSet<Span> ret = new HashSet<Span>();
        //System.out.println("next from "+r+","+c);
        while (!bw[r][c] && tms[r+1][c] == 0)
            r++;
        // now we have a space with a wall below, check sides
        int left = c;
        while (!lw[r][left]) {
            left--;
            if (!bw[r][left] && tms[r+1][left] == 0) {
                ret.addAll(next(lw,bw,tms,r,left));
                break;
            }
        }
        int right = c;
        while (right < lw[0].length-1 && !lw[r][right+1]) {
            right++;
            if (!bw[r][right] && tms[r+1][right] == 0) {
                ret.addAll(next(lw,bw,tms,r,right));
                break;
            }
        }
        if (ret.isEmpty())
            ret.add(new Span(r,left,right));
        return ret;
    }
}

class Span {
    public Span(int row, int l, int r) { this.row = row; left = l; right = r;}
    public int hashCode() {return 10000*row+100*left+right;}
    public boolean equals(Object o) { 
        Span os = (Span)(o);
        return os.row == row && os.left == left && os.right == right;}
    public int row, left, right;
}


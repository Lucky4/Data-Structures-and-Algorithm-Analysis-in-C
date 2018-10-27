import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;


public class ADT {
    public Map S;
    public int[] relations;

    public ADT(Map S) {
        this.S = S;
        this.relations = new int[10];

        Iterator<Map.Entry> entries = this.S.entrySet().iterator();

        while (entries.hasNext()) {
            Map.Entry entry = (Map.Entry) entries.next();
            Integer key = (Integer) entry.getKey();
            Integer value = (Integer) entry.getValue();
            this.UnionEnhace(key, value);
        }
    }

    public void Initialize() {
        for (int i = 0; i < this.relations.length; i++) {
            this.relations[i] = 0;
        }
    }

    public void Union(int elem1, int elem2) {
        this.relations[elem1] = elem2;
    }

    public void UnionEnhace(int elem1, int elem2) {
        if (this.relations[elem1] > this.relations[elem2]) {
            this.relations[elem1] = elem2;
        } else {
            if (this.relations[elem1] == this.relations[elem2]) {
                this.relations[elem2] -= 1;
            }
            this.relations[elem1] = elem2;
        }
    }

    public int Find(int elem) {
        if (this.relations[elem] <= 0) {
            return elem;
        } else {
            return Find(this.relations[elem]);
        }
    }

    public static void main(String args[]) {
        Map<Integer, Integer> S = new HashMap<Integer, Integer>();
        S.put(6, 5);
        S.put(8, 7);
        S.put(7, 5);
        S.put(4, 5);

        ADT obj = new ADT(S);

        System.out.println(obj.Find(4));
        System.out.println(obj.Find(5));
        System.out.println(obj.Find(6));
        System.out.println(obj.Find(7));
        System.out.println(obj.Find(8));
    }
}

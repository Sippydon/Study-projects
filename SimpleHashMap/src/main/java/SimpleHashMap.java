import java.util.*;

public class SimpleHashMap<K, V> implements Map<K, V> {
    private int size = 0;
    private final double capacity = 0.8;
    private Node<K, V>[] table;

    public SimpleHashMap() {
        this.table = (Node<K, V>[]) new Node[16];
    }

    static class Node<K, V> implements Map.Entry<K, V> {
        final int hash;
        final K key;
        V value;
        Node<K, V> next;

        public Node(int hash, K key, V value) {
            this.hash = hash;
            this.key = key;
            this.value = value;
            next = null;
        }

        @Override
        public K getKey() {
            return key;
        }

        @Override
        public V getValue() {
            return value;
        }

        @Override
        public V setValue(V value) {
            return value;
        }

        public void setNext(Node<K, V> next) {
            this.next = next;
        }

        public Node<K, V> getNext() {
            return next;
        }

        public boolean equals(Node<K, V> node) {
            return this.hash == node.hash && this.key.equals(node.key);
        }
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        return table[position(hash(key))] != null;
    }

    @Override
    public boolean containsValue(Object value) {
        for (Node<K, V> node : table) {
            if (node == null) {
                continue;
            }
            if (node.value.equals(value)) {
                return true;
            } else if (node.next != null) {
                Node<K, V> next = node.next;
                do {
                    if (next.value.equals(value)) {
                        return true;
                    }
                    next = next.next;
                } while (next != null);
            }
        }
        return false;
    }

    @Override
    public V get(Object key) {
        return table[position(hash(key))].value;
    }

    @Override
    public V put(K key, V value) {
        Node<K, V> tmp = new Node<K, V>(hash(key), key, value);
        int pos = position(tmp.hash);

        resize();

        if (table[pos] == null) {
            table[pos] = tmp;
            size++;
        } else {
            Node<K, V> n = table[pos];
            do {
                if (n.equals(tmp)) {
                    n.value = tmp.value;
                    return n.value;
                } else if (!n.equals(tmp) && n.next == null) {
                    n.setNext(tmp);
                    break;
                }
                n = n.next;
            } while (n != null);
        }
        return null;
    }

    @Override
    public V remove(Object key) {
        int pos = position(hash(key));
        Node<K, V> tmp = table[pos];
        if (tmp != null) {
            table[pos] = tmp.next;
            return tmp.value;
        }
        return null;
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        for (Entry<? extends K, ? extends V> entry : m.entrySet()) {
            put(entry.getKey(), entry.getValue());
        }
    }

    @Override
    public void clear() {
        Arrays.fill(table, null);
    }

    private int hash(Object key) {
        int h;
        return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
    }

    private int position(int hash) {
        return hash & (table.length - 1);
    }

    private void resize() {
        if(size >= table.length * capacity) {
            Node<K, V>[] oldTable = table;
            size = 0;

            table = (Node<K, V>[]) new Node[table.length * 2];

            for (Node<K, V> node : oldTable) {
                if (node != null) {
                    Node<K, V> tmp;
                    tmp = node;
                    put(tmp.getKey(), tmp.getValue());
                    if (tmp.next != null) {
                        do {
                            Node<K, V> next = tmp.next;
                            put(next.getKey(), next.getValue());
                            tmp = next;
                        } while (tmp.next != null);
                    }
                }
            }
        }
    }

    @Override
    public Set<K> keySet() {
        Set<K> set = new HashSet<>();
        for (Node<K, V> node : table) {
            if (node != null) {
                set.add(node.key);
                if (node.next != null) {
                    Node<K, V> tmp = node.next;
                    do {
                        set.add(tmp.key);
                        tmp = tmp.next;
                    } while (tmp != null);
                }
            }
        }
        return set;
    }

    @Override
    public Collection<V> values() {
        Collection<V> collection = new ArrayList<>();
        for (Node<K, V> node : table) {
            if (node != null) {
                collection.add(node.value);
                if (node.next != null) {
                    Node<K, V> tmp = node.next;
                    do {
                        collection.add(tmp.value);
                    } while (tmp.next != null);
                }
            }
        }
        return collection;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        Set<Map.Entry<K, V>> set = new HashSet<>();
        for (Node<K, V> node : table) {
            if (node != null) {
                set.add(node);
                if (node.next != null) {
                    Node<K, V> tmp = node.next;
                    do {
                        set.add(tmp);
                        tmp = tmp.next;
                    }while (tmp != null);
                }
            }
        }
        return set;
    }
}

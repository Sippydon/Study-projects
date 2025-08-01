import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;



class SimpleHashMapTest {
    private final SimpleHashMap<String, String> simpleHashMap = new SimpleHashMap<>();
    private final Map<String, String> originalMap = new HashMap<>();


    @BeforeEach
    void setUp() {
        simpleHashMap.put("test", "1");
        simpleHashMap.put("tesst", "2");
        simpleHashMap.put("tessst", "3");
        simpleHashMap.put("tesssst", "4");
        simpleHashMap.put("tessssst", "5");

        originalMap.put("test", "1");
        originalMap.put("tesst", "2");
        originalMap.put("tessst", "3");
        originalMap.put("tesssst", "4");
        originalMap.put("tessssst", "5");
    }

    @AfterEach
    void tearDown() {
        simpleHashMap.clear();
        originalMap.clear();
    }

    @Test
    void isEmpty() {
        Assertions.assertEquals(originalMap.isEmpty(), simpleHashMap.isEmpty());
    }

    @Test
    void containsKey() {
        Assertions.assertEquals(originalMap.containsKey("test"), simpleHashMap.containsKey("test"));
        Assertions.assertEquals(originalMap.containsKey("tesst"), simpleHashMap.containsKey("tesst"));
        Assertions.assertEquals(originalMap.containsKey("tessst"), simpleHashMap.containsKey("tessst"));
        Assertions.assertEquals(originalMap.containsKey("tesssst"), simpleHashMap.containsKey("tesssst"));
        Assertions.assertEquals(originalMap.containsKey("tessssst"), simpleHashMap.containsKey("tessssst"));
    }

    @Test
    void containsValue() {
        Assertions.assertEquals(originalMap.containsValue("1"), simpleHashMap.containsValue("1"));
        Assertions.assertEquals(originalMap.containsValue("2"), simpleHashMap.containsValue("2"));
        Assertions.assertEquals(originalMap.containsValue("3"), simpleHashMap.containsValue("3"));
        Assertions.assertEquals(originalMap.containsValue("4"), simpleHashMap.containsValue("4"));
        Assertions.assertEquals(originalMap.containsValue("5"), simpleHashMap.containsValue("5"));
    }

    @Test
    void get() {
        Assertions.assertNull(originalMap.get("null"));
    }

    @Test
    void put() {
        Assertions.assertNull(originalMap.get("new value"));
    }

    @Test
    void remove() {
        Assertions.assertEquals(originalMap.remove("test"), simpleHashMap.remove("test"));
    }

    @Test
    void resize() {
        for (int i = 6; i < 43; i++) {
            simpleHashMap.put("test" + i, String.valueOf(i));
            originalMap.put("test" + i, String.valueOf(i));
        }

        for (int i = 1; i < 43; i++) {
            Assertions.assertTrue(simpleHashMap.containsValue(String.valueOf(i)));
        }

    }

    @Test
    void keySet() {
        Assertions.assertEquals(originalMap.keySet(), simpleHashMap.keySet());
    }

    @Test
    void values() {
        Assertions.assertEquals(originalMap.values().toString(), simpleHashMap.values().toString());
    }

    @Test
    void entrySet() {
        Assertions.assertEquals(originalMap.entrySet(), simpleHashMap.entrySet());
    }
}
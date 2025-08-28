1: Why can’t Bloom Filters guarantee “yes”?
Because multiple elements can set the same bits → collisions cause false positives. It can only guarantee “definitely not.”

2: Why can’t we delete from a standard Bloom Filter?
Bits are shared by many items. Clearing bits for one item may erase bits needed by others → causes false negatives.

3️: What will happen if we keep adding elements without limit?
The bit array fills with 1s → false positive rate rises to 100% → filter becomes useless.

4️: Which is more costly: false positives or false negatives? Why?
False negatives are worse in most cases (miss real data). That’s why Bloom filters are designed to never allow them. False positives just waste extra lookup time.

5️: Can a Bloom Filter replace a Hash Table completely? Why/why not?
No. Bloom filters only test membership, they don’t store keys/values or allow retrieval. They complement hash tables, not replace them.

6️: If I use only one hash function, is it still a Bloom Filter? What problems might arise?
Yes, but inefficient. With one hash, collisions rise fast, distribution is poor, and false positives become common.

7️: If my Bloom Filter bit array is completely filled with 1s, what will happen?
Every lookup will return “possibly present.” False positives = 100%. The filter is useless.
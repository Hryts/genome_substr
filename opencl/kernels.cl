//typedef struct {
//    short ch;
//    short id;
//    size_t first_child;
//    size_t second_child;
//    size_t third_child;
//    size_t fourth_child;
//} Node;


//__kernel void add(ulong n, global const char *input, global char *output, global Node *trie) {
//    size_t currentIndex = get_global_id(0);
//    printf("%d", currentIndex);
//    if(currentIndex < n) {
//        size_t nextIndex;
//        char currentLetter = input[currentIndex];
//        Node currentNode = trie[0];
//        int childIndex;
//    //    printf("%c", currentNode.ch);
//
//        while(true) {
//            printf("%c", currentNode.ch);
//            if(currentLetter == 'A') childIndex = currentNode.first_child;
//            if(currentLetter == 'C') childIndex = currentNode.second_child;
//            if(currentLetter == 'T') childIndex = currentNode.third_child;
//            if(currentLetter == 'G') childIndex = currentNode.fourth_child;
//    //        printf("%d", childIndex);
//
//            if(childIndex == 0) return;
//            else {
//                nextIndex = childIndex;
//                currentIndex++;
//                currentLetter = input[currentIndex];
//                currentNode = trie[nextIndex];
//                if (currentNode.id != 0) printf("%d\n", currentNode.id);
//            }
//        }
//    }
//}


__kernel void add(ulong n, global const char *input, global char *output, global char *chs, global size_t *ids, global size_t *firsts, global size_t *seconds, global size_t *thirds, global size_t *fourths) {
    size_t currentIndex = get_global_id(0);
    printf("%d", currentIndex);
    if(currentIndex < n) {
        size_t nextIndex = 0;
        char currentLetter = input[currentIndex];
//        Node currentNode = trie[0];
        int childIndex;
        //    printf("%c", currentNode.ch);

        while(true) {
//            printf("%c", currentNode.ch);
            if(currentLetter == 'A') childIndex = firsts[nextIndex];
            if(currentLetter == 'C') childIndex = seconds[nextIndex];
            if(currentLetter == 'T') childIndex = thirds[nextIndex];
            if(currentLetter == 'G') childIndex = fourths[nextIndex];
            //        printf("%d", childIndex);

            if(childIndex == 0) return;
            else {
                currentIndex++;
                currentLetter = input[currentIndex];
                if (ids[nextIndex] != 0) printf("%d\n", ids[nextIndex]);
                nextIndex = childIndex;
            }
        }
    }
}
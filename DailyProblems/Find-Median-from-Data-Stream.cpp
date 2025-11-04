class MedianFinder {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int> , greater<int>> minHeap;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        // give preference to maxHeap
        if(maxHeap.empty() || num <= maxHeap.top()){
            maxHeap.push(num);
        }else{
            minHeap.push(num);
        }

        //Balance Heap
        if(maxHeap.size() > minHeap.size() + 1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }else if(minHeap.size() > maxHeap.size() ){
             maxHeap.push(minHeap.top());
             minHeap.pop();
        }
    }
    
    double findMedian() {
        if((minHeap.size() + maxHeap.size())%2 == 0){
            return (minHeap.top() + maxHeap.top())/2.0;
        }
        return maxHeap.top();
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
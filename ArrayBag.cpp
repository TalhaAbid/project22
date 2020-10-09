#include "ArrayBag.hpp"

template<typename ItemType>
ArrayBag<ItemType>::ArrayBag(): item_count_(0){
    //default constructor
}
template<typename ItemType>
int ArrayBag<ItemType>::getCurrentSize() const{
   return item_count_; // return the curr item Count

}
template<typename ItemType>
bool ArrayBag<ItemType>::isEmpty() const{
    //return if curr item_count_ is 0
    return item_count_ == 0;
}


template<typename ItemType>
bool ArrayBag<ItemType>::add(const ItemType& new_entry){
    if (getCurrentSize() == DEFAULT_CAPACITY){
        return false;
    } else {
        items_[getCurrentSize() - 1] = new_entry;
        item_count_++;
        return true;
    }
}

template<typename ItemType>
bool ArrayBag<ItemType>::remove(const ItemType &an_entry){
    int index = getIndexOf(an_entry); // get the index of the item
    if (getIndexOf(an_entry) == -1){  // if index == -1 
        return false; // return false since item not in array
    } else { // item is in array
        items_[index] = items_[getCurrentSize() - 1]; 
        // replace the item to be removed with the item at the end
        item_count_--; // reduce the current size by 1
        return true;
    }
    return false;
}


template<typename ItemType>
void ArrayBag<ItemType>::clear(){
    item_count_ = 0; // set item count to 0
}

template<typename ItemType>
bool ArrayBag<ItemType>::contains(const ItemType &an_entry) const{
    return (getIndexOf(an_entry) != -1);
    // if the index is not -1 then the item will be in the array
}

template<typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType &an_entry) const{
    int count = 0; // set counter
    for (int i = 0; i < getCurrentSize(); i++){ // loop over current array
        if (items_[i] == an_entry) // check if curr item == entry
            count++; // increase the count if equal
    }
    return count;
}

template<typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType &target) const{
    if (getFrequencyOf(target) == 0){
        // check the frequency, if 0 return -1
        return -1;
    } else {
        for (int i =0; i < getCurrentSize(); i++){ // loop over curr array
            if (items_[i] == target){ // check if the curr item == target
                return i; // return index of the first occurance
            }
        }
    }
    return -1;
}
template<typename ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const{
    vector<ItemType> temp;
    for (int i = 0; i < item_count_; i++){
        temp.push_back(items_[i]);
    }
    return temp;
}

template<typename ItemType>
void ArrayBag<ItemType>::operator+=(const ArrayBag<ItemType> &a_bag){
    if (this->getCurrentSize() == DEFAULT_CAPACITY){
        // if the LHS bag is already full don't do anything
        return;
    } else if (a_bag.getCurrentSize() == 0){
        // if the RHS bag is empty don't do anything
        return;
    } else {
        int startIndexRHS;
        // set the starting index of RHS BAG to 0;
        startIndexRHS = 0;
        auto temp = a_bag.toVector(); 
        while (this->getCurrentSize() != DEFAULT_CAPACITY && startIndexRHS <= a_bag.getCurrentSize() -1){
        // loop while current bag isnt full and dont go out of bounds in the second array
            this->add(temp[startIndexRHS]);
            startIndexRHS++;
        }
    }
}
template<typename ItemType>
void ArrayBag<ItemType>::operator-=(const ArrayBag<ItemType> &a_bag){
    if (this->getCurrentSize() == 0){
        return; // if LHS bag is empty do nothing
    } else if (a_bag.getCurrentSize() == 0){
        // if the RHS bag is empty don't do anything
        return;
    } else {
        auto temp = a_bag.toVector(); // itterate over items in RHS bag
        for(auto item: temp){ 
            if (this->contains(item)){ // if item is in both
                this->remove(item); //  remove the item from LHS
            }
        }
    }
}
template<typename ItemType>
void ArrayBag<ItemType>::operator/=(const ArrayBag<ItemType> &a_bag){
    if (this->getCurrentSize() == 0){
        return; // if LHS bag is empty do nothing
    } else if (a_bag.getCurrentSize() == 0){
        // if the RHS bag is empty, clear LHS bag
        this->clear(); 
    } else {
        auto temp = this->toVector();
        for (auto item: temp){
            if (!(a_bag.contains(item))){ // if LHS[i] is not in  RHS 
                this->remove(item); // remove it from LHS
            }
        }
    }
}
template<typename ItemType>
bool ArrayBag<ItemType>::operator==(const ArrayBag<ItemType> &a_bag){
    if (this->getCurrentSize() != a_bag.getCurrentSize()){
        return false;
    } else {
        // get the set difference 
        this->operator-=(a_bag);
        // if two bags are the same then set difference will make the LHS empty
        return item_count_ == 0;
    }
    return false;
}

template<typename ItemType>
bool ArrayBag<ItemType>::operator!=(const ArrayBag<ItemType> &a_bag){
    return false;
}

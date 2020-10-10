#include "ArrayBag.hpp"
#include <iostream>
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
    if (item_count_ == DEFAULT_CAPACITY){
        return false;
    } else {
        items_[getCurrentSize() - 1] = new_entry;
        item_count_++;
        return true;
    }
}

template<typename ItemType>
bool ArrayBag<ItemType>::remove(const ItemType &an_entry){
    int index = getIndexOf(an_entry);
    if (!isEmpty() && index >= 0){
        item_count_--;
        items_[index]  == items_[item_count_];
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
    return (!(getIndexOf(an_entry) == -1));
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
        int index = -1;
        for (int i =0; i < item_count_; i++){ // loop over curr array
                std::cout << items_[i] << std::endl;
                if (items_[i] == target){ // check if the curr item == target
                index = i; // return index of the first occurance
                return i;
            }
        }
    return index;
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
    } else if (a_bag.isEmpty()){
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
    } else if (a_bag.isEmpty()){
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
    } else if (a_bag.isEmpty()){
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
        for (int i = 0; i < item_count_; i++){
            if (a_bag.contains(items_[i]) == false) {
                return false;
            }
        }
    }
    return false;
    
}

template<typename ItemType>
bool ArrayBag<ItemType>::operator!=(const ArrayBag<ItemType> &a_bag){
    return !(this->operator==(a_bag));
}

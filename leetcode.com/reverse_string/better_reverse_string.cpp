 void reverseString(vector<char>& s) {
        int a = 0, b = s.size()-1;
        for(std::size_t it = s.size()/2;it > 0; it--){
            std::swap(s[a], s[b]);
            ++a;
            --b;
        }
    }



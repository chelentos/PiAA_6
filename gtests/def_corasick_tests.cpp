#include "gtest/gtest.h"
#include "Corasick.h"

namespace {

    Bohr Resault(const string& text, const vector<string>& patterns) {
       Bohr bohr;
       for(const auto& patt : patterns) {
          bohr.add_string_to_bohr(patt);
       }
       bohr.find_all_pos(text);
       return bohr;
    }
    
    void comparator(vector<int> v1, vector<int> v2) {
        for (size_t i = 0; i < v1.size(); ++i) {
            EXPECT_EQ(v1[i], v2[i]);
        }
    }
    
    struct DefCorasickTest
    {
        string text;
    	vector<string> patterns;
    	vector<int> expected_indexes;
    	vector<int> expected_pattern_nums;
    };
    
    class DefCorasickTests : public ::testing::TestWithParam<DefCorasickTest>
    {
    public:
    
    	virtual void SetUp() override {
    	    string _text = GetParam().text;
    	    vector<string> _patterns = GetParam().patterns;
    	    bohr = Resault(_text, _patterns);
    	}
        virtual void TearDown() override { }
    
    protected:
    
        Bohr bohr;
    };
    
    INSTANTIATE_TEST_CASE_P(DefaultCases, DefCorasickTests,
    ::testing::Values(
        DefCorasickTest{"CCCA", {"CC"}, {0, 1}, {0, 0}},
        DefCorasickTest{"ATCTCA", {"TC", "A"}, {0, 1, 3, 5}, {2, 1, 1, 2}},
        DefCorasickTest{"TCAGTAGC", {"AG", "TA", "C"}, {1, 2, 4, 5, 7}, {2, 0, 1, 0, 2}},
        DefCorasickTest{"AAAAAAA", {"C"}, {}, {}}
    ));
    
    INSTANTIATE_TEST_CASE_P(NoPatternCases, DefCorasickTests,
    ::testing::Values(
        DefCorasickTest{"AAAAAAA", {"C"}, {}, {}},
        DefCorasickTest{"AGTCGTT", {"N"}, {}, {}}
    ));
    
    TEST_P(DefCorasickTests, PSTest) {
        ASSERT_EQ(GetParam().expected_indexes.size(), bohr.GetIndexes().size());
    
        ASSERT_EQ(GetParam().expected_pattern_nums.size(), bohr.GetPatternNums().size());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
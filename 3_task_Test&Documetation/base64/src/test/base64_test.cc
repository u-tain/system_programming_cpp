#include<gtest/gtest.h>
#include<iostream>
#include<algorithm>
#include <base64/base64.hh>

using namespace std;

TEST(base64, encode) {
        string y;
        y.resize( base64_encoded_size(3));
        base64_encode("Man",3,&y[0]);
        EXPECT_EQ("TWFu",y);

        string z;
        z.resize(base64_encoded_size(0));
        base64_encode("",0,&z[0]);
        EXPECT_EQ("",z);

        string x;
        x.resize(base64_encoded_size(1));
        base64_encode("f",1,&x[0]);
        EXPECT_EQ("Zg==",x);

        string v;
        v.resize(base64_encoded_size(2));
        base64_encode("fo",2,&v[0]);
        EXPECT_EQ("Zm8=",v);

        string b;
        b.resize(base64_encoded_size(3));
        base64_encode("foo",3,&b[0]);
        EXPECT_EQ("Zm9v",b);

        string a;
        a.resize(base64_encoded_size(6));
        base64_encode("foobar",6,&a[0]);
        EXPECT_EQ("Zm9vYmFy",a);

        string s;
        s.resize(base64_encoded_size(5));
        base64_encode("+cat/",5,&s[0]);
        EXPECT_EQ("K2NhdC8=",s);

        string m;
        m.resize(base64_encoded_size(5));
        base64_encode("56foo",5,&m[0]);
        EXPECT_EQ("NTZmb28=",m);
}

TEST(base64, decode) {
        string p;
        p.resize(base64_max_decoded_size(4));
        base64_decode("TWFu",4,&p[0]);
        EXPECT_EQ("Man",p);

        string o;
        o.resize(base64_max_decoded_size(0));
        base64_decode("",0,&o[0]);
        EXPECT_EQ("",o);

        string f;
        f.resize(base64_max_decoded_size(8));
        base64_decode("K2NhdC8=",8,&f[0]);
        EXPECT_EQ(0,strncmp("+cat/",&f[0],5));

        string g;
        g.resize(base64_max_decoded_size(4));
        base64_decode("Zg==",4,&g[0]);
        EXPECT_EQ(0, strncmp("f",&g[0],1));

        string h;
        h.resize(base64_max_decoded_size(4));
        base64_decode("Zm8=",4,&h[0]);
        EXPECT_EQ(0,strncmp("fo",&h[0],2));

        string j;
        j.resize(base64_max_decoded_size(4));
        base64_decode("Zm9v",4,&j[0]);
        EXPECT_EQ(0,strncmp("foo",&j[0],3));

        string k;
        k.resize(base64_max_decoded_size(8));
        base64_decode("Zm9vYmFy",8,&k[0]);
        EXPECT_EQ(0,strncmp("foobar",&k[0],6));

        string l;
        l.resize(base64_max_decoded_size(5));
        EXPECT_THROW({
        try{ base64_decode("TWFud",5,&l[0]);}
        catch(const invalid_argument& err){
        EXPECT_STREQ("bad base64 string", err.what());
        throw;}},invalid_argument);
}

        struct Decode_params {
                const char* elem;
        };
        class exceptions_test: public ::testing::TestWithParam<Decode_params> {};

        TEST_P(exceptions_test,_){
        const  Decode_params& param = GetParam();
        string y;
        y.resize(base64_max_decoded_size(strlen(param.elem)));
        EXPECT_THROW({
        try{ base64_decode(param.elem,strlen(param.elem),&y[0]);}
        catch(const invalid_argument& err){
        EXPECT_STREQ("bad base64 string",err.what());
        throw;}},invalid_argument);
        }

        INSTANTIATE_TEST_CASE_P(
        _,
        exceptions_test,
        ::testing::Values(
                        Decode_params{"zxcvbnяf"},
                        Decode_params{"zxcvbn%f"},
                        Decode_params{"чfhdjskf"},
                        Decode_params{"%xcvmmff"},
                        Decode_params{"zчdfgskf"},
                        Decode_params{"z%xcbnxf"},
                        Decode_params{"фыв"},
                        Decode_params{"==чcd"},
                        Decode_params{"xcv"},
                        Decode_params{"df=%"},
                        Decode_params{"df%="},
                        Decode_params{"zxcи"},
                        Decode_params{"zxc%"},
                        Decode_params{"zx%c"},
                        Decode_params{"zxиc"},
                        Decode_params{"z%xc"},
                        Decode_params{"zиxc"},
                        Decode_params{"%zxc"},
                        Decode_params{"иzxc"},
                        Decode_params{"%cv="},
                        Decode_params{"c%v="},
                        Decode_params{"zиx="},
                        Decode_params{"zx%="},
                        Decode_params{"zxи="},
                        Decode_params{"иzx="},
                        Decode_params{"%c=="},
                        Decode_params{"c%=="},
                        Decode_params{"мc=="},
                        Decode_params{"cм=="},
                        Decode_params{"zxc%zxcv"},
                        Decode_params{"zxвzxcvb"},
                        Decode_params{"zx%zxcvb"},
                        Decode_params{"zxcаzxcv"}
                        )
        );


TEST(base64, encode_size){
        string z;
        z.resize(base64_encoded_size(5));
        EXPECT_EQ(z.length(),8u);

        string x;
        EXPECT_THROW({
        try{ x.resize(base64_encoded_size(0xffffffff80000000));}
        catch(const length_error& err){
        EXPECT_STREQ("base64 length is too large",err.what());
        throw;}},length_error);
}

TEST(base64, decode_max_size){
        size_t len = base64_max_decoded_size(8);
        EXPECT_EQ(len, 6u);
}
TEST(base64, ch_to_indx){
        string x;
        EXPECT_THROW({
        try{ x.resize(char_to_index(128));}
        catch(const invalid_argument& err){
        EXPECT_STREQ("bad base64 string",err.what());
        throw;}},invalid_argument);

        string y;
        EXPECT_THROW({
        try{ x.resize(char_to_index(129));}
        catch(const invalid_argument& err){
        EXPECT_STREQ("bad base64 string",err.what());
        throw;}},invalid_argument);
}

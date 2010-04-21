/*
* EMSA-Raw
* (C) 1999-2007 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#include <botan/emsa_raw.h>

namespace Botan {

/*
* EMSA-Raw Encode Operation
*/
void EMSA_Raw::update(const byte input[], u32bit length)
   {
   message.append(input, length);
   }

/*
* Return the raw (unencoded) data
*/
SecureVector<byte> EMSA_Raw::raw_data()
   {
   SecureVector<byte> buf = message;
   message.destroy();
   return buf;
   }

/*
* EMSA-Raw Encode Operation
*/
SecureVector<byte> EMSA_Raw::encoding_of(const MemoryRegion<byte>& msg,
                                         u32bit,
                                         RandomNumberGenerator&)
   {
   return msg;
   }

/*
* EMSA-Raw Verify Operation
*/
bool EMSA_Raw::verify(const MemoryRegion<byte>& coded,
                      const MemoryRegion<byte>& raw,
                      u32bit)
   {
   if(coded.size() == raw.size())
      return (coded == raw);

   if(coded.size() > raw.size())
      return false;

   // handle zero padding differences
   const u32bit leading_zeros_expected = raw.size() - coded.size();

   bool same_modulo_leading_zeros = true;

   for(u32bit i = 0; i != leading_zeros_expected; ++i)
      if(raw[i])
         same_modulo_leading_zeros = false;

   if(!same_mem(&coded[0], &raw[leading_zeros_expected], coded.size()))
      same_modulo_leading_zeros = false;

   return same_modulo_leading_zeros;
   }

}

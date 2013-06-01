/* This file is part of the 'stringi' library.
 * 
 * Copyright 2013 Marek Gagolewski, Bartek Tartanus, Marcin Bujarski
 * 
 * 'stringi' is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 'stringi' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with 'stringi'. If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef __unicoder16_h
#define __unicoder16_h





/**
 * A class to handle conversion between R character vectors and UTF-16 string vectors
 * @version 0.1 (Marek Gagolewski)
 * @version 0.2 (Marek Gagolewski) - lastMatcher cache, supports auto-vectorization
 * @version 0.3 (Marek Gagolewski) - improved ASCII performance (seperate ucnv)
 * @version 0.4 (Marek Gagolewski) - now NAs are marked as NULLs in str
 */
class StriContainerUTF16 : public StriContainerUTF_Base {
   
   private:
      
      UnicodeString** str;       ///< data - \code{UnicodeString}s 
      RegexMatcher* lastMatcher; ///< recently used \code{RegexMatcher}
#ifndef NDEBUG
      R_len_t debugMatcherIndex;  ///< used by vectorize_getMatcher (internally - check)
#endif


   public:
      
      StriContainerUTF16();
      StriContainerUTF16(SEXP rstr, R_len_t nrecycle, bool shallowrecycle=true);
      StriContainerUTF16(StriContainerUTF16& container);
      ~StriContainerUTF16();
      StriContainerUTF16& operator=(StriContainerUTF16& container);
      SEXP toR(R_len_t i) const;
      SEXP toR() const;
      
      
      /** check if the vectorized ith element is NA
       */
      inline bool isNA(int i) const {
#ifndef NDEBUG
         if (i < 0 || i >= nrecycle)
            error("StriContainerUTF16::isNA(): INDEX OUT OF BOUNDS");
#endif
         return (str[i%n] == NULL);
      }
      
      
      /** get the vectorized ith element
       */
      const UnicodeString& get(int i) const {
#ifndef NDEBUG
         if (i < 0 || i >= nrecycle)
            error("StriContainerUTF16::get(): INDEX OUT OF BOUNDS");
         if (str[i%n] == NULL)
            error("StriContainerUTF16::get(): isNA");
#endif
         return (*(str[i%n]));
      }
      
      /** get the vectorized ith element
       */
      UnicodeString& getWritable(int i) {
#ifndef NDEBUG
         if (isShallow)              
            error("StriContainerUTF16::getWritable(): shallow StriContainerUTF16");
         if (n != nrecycle)          
            error("StriContainerUTF16::getWritable(): n!=nrecycle");
         if (i < 0 || i >= n)        
            error("StriContainerUTF16::getWritable(): INDEX OUT OF BOUNDS");
         if (str[i%n] == NULL) 
            error("StriContainerUTF16::getWritable(): isNA");
#endif
         return (*(str[i%n])); // in fact, "%n" is not necessary
      }
      
      /** set the vectorized ith element
       */
      void set(int i, const UnicodeString& s) {
#ifndef NDEBUG
         if (isShallow)              
            error("StriContainerUTF16::set(): shallow StriContainerUTF16");
         if (n != nrecycle)          
            error("StriContainerUTF16::set(): n!=nrecycle");
         if (i < 0 || i >= n)        
            error("StriContainerUTF16::set(): INDEX OUT OF BOUNDS");
         if (str[i%n] == NULL) 
            error("StriContainerUTF16::set(): isNA");
#endif
         *(str[i%n]) = s; // in fact, "%n" is not necessary
      }
      
      RegexMatcher* vectorize_getMatcher(R_len_t i);
};

#endif
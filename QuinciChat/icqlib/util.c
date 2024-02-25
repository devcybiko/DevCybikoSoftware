/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

/*
 * $Id: util.c,v 1.6 2001/07/31 01:59:51 cyreve Exp $
 *
 * Copyright (C) 1998-2001, Denis V. Dmitrienko <denis@null.net> and
 *                          Bill Soudan <soudan@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdlib.h>
#include <ctype.h>

#include "icqlib.h"
#include "stdpackets.h"

/*
 * This list of countries should be sorted according to country code.
 * When adding new country, please preserve the order!
 */
icq_ArrayType icq_Countries[] = {
  {"Unspecified",0},
  {"USA",1},
  {"Russia",7},
  {"Egypt",20},
  {"South Africa",27},
  {"Greece",30},
  {"Netherlands",31},
  {"Belgium",32},
  {"France",33},
  {"Spain",34},
  {"Hungary",36},
  {"Italy",39},
  {"Romania",40},
  {"Switzerland",41},
  {"Czech Republic",42},
  {"Austria",43},
  {"United Kingdom",44},
  {"Denmark",45},
  {"Sweden",46},
  {"Norway",47},
  {"Poland",48},
  {"Germany",49},
  {"Peru",51},
  {"Mexico",52},
  {"Cuba",53},
  {"Argentina",54},
  {"Brazil",55},
  {"Chile",56},
  {"Colombia",57},
  {"Venezuela",58},
  {"Malaysia",60},
  {"Australia",61},
  {"Indonesia",62},
  {"Philippines",63},
  {"New Zealand",64},
  {"Singapore",65},
  {"Thailand",66},
  {"Japan",81},
  {"Korea (Republic of)",82},
  {"Vietnam",84},
  {"China",86},
  {"Turkey",90},
  {"India",91},
  {"Pakistan",92},
  {"Afghanistan",93},
  {"Sri Lanka",94},
  {"Myanmar",95},
  {"Iran",98},
  {"Anguilla",101},
  {"Antigua",102},
  {"Bahamas",103},
  {"Barbados",104},
  {"Bermuda",105},
  {"British Virgin Islands",106},
  {"Canada",107},
  {"Cayman Islands",108},
  {"Dominica",109},
  {"Dominican Republic",110},
  {"Grenada",111},
  {"Jamaica",112},
  {"Montserrat",113},
  {"Nevis",114},
  {"St. Kitts",115},
  {"St. Vincent and the Grenadines",116},
  {"Trinidad and Tobago",117},
  {"Turks and Caicos Islands",118},
  {"Barbuda",120},
  {"Puerto Rico",121},
  {"Saint Lucia",122},
  {"United States Virgin Islands",123},
  {"Morocco",212},
  {"Algeria",213},
  {"Tunisia",216},
  {"Libya",218},
  {"Gambia",220},
  {"Senegal Republic",221},
  {"Mauritania",222},
  {"Mali",223},
  {"Guinea",224},
  {"Ivory Coast",225},
  {"Burkina Faso",226},
  {"Niger",227},
  {"Togo",228},
  {"Benin",229},
  {"Mauritius",230},
  {"Liberia",231},
  {"Sierra Leone",232},
  {"Ghana",233},
  {"Nigeria",234},
  {"Chad",235},
  {"Central African Republic",236},
  {"Cameroon",237},
  {"Cape Verde Islands",238},
  {"Sao Tome and Principe",239},
  {"Equatorial Guinea",240},
  {"Gabon",241},
  {"Congo",242},
  {"Zaire",243},
  {"Angola",244},
  {"Guinea-Bissau",245},
  {"Diego Garcia",246},
  {"Ascension Island",247},
  {"Seychelle Islands",248},
  {"Sudan",249},
  {"Rwanda",250},
  {"Ethiopia",251},
  {"Somalia",252},
  {"Djibouti",253},
  {"Kenya",254},
  {"Tanzania",255},
  {"Uganda",256},
  {"Burundi",257},
  {"Mozambique",258},
  {"Zambia",260},
  {"Madagascar",261},
  {"Reunion Island",262},
  {"Zimbabwe",263},
  {"Namibia",264},
  {"Malawi",265},
  {"Lesotho",266},
  {"Botswana",267},
  {"Swaziland",268},
  {"Mayotte Island",269},
  {"St. Helena",290},
  {"Eritrea",291},
  {"Aruba",297},
  {"Faeroe Islands",298},
  {"Greenland",299},
  {"Gibraltar",350},
  {"Portugal",351},
  {"Luxembourg",352},
  {"Ireland",353},
  {"Iceland",354},
  {"Albania",355},
  {"Malta",356},
  {"Cyprus",357},
  {"Finland",358},
  {"Bulgaria",359},
  {"Lithuania",370},
  {"Latvia",371},
  {"Estonia",372},
  {"Moldova",373},
  {"Armenia",374},
  {"Belarus",375},
  {"Andorra",376},
  {"Monaco",377},
  {"San Marino",378},
  {"Vatican City",379},
  {"Ukraine",380},
  {"Yugoslavia",381},
  {"Croatia",385},
  {"Slovenia",386},
  {"Bosnia and Herzegovina",387},
  {"Republic of Macedonia",389},
  {"Falkland Islands",500},
  {"Belize",501},
  {"Guatemala",502},
  {"El Salvador",503},
  {"Honduras",504},
  {"Nicaragua",505},
  {"Costa Rica",506},
  {"Panama",507},
  {"St. Pierre and Miquelon",508},
  {"Haiti",509},
  {"Guadeloupe",590},
  {"Bolivia",591},
  {"Guyana",592},
  {"Ecuador",593},
  {"French Guiana",594},
  {"Paraguay",595},
  {"Martinique",596},
  {"Suriname",597},
  {"Uruguay",598},
  {"Netherlands Antilles",599},
  {"Saipan Island",670},
  {"Guam",671},
  {"Christmas Island",672},
  {"Brunei",673},
  {"Nauru",674},
  {"Papua New Guinea",675},
  {"Tonga",676},
  {"Solomon Islands",677},
  {"Vanuatu",678},
  {"Fiji Islands",679},
  {"Palau",680},
  {"Wallis and Futuna Islands",681},
  {"Cook Islands",682},
  {"Niue",683},
  {"American Samoa",684},
  {"Western Samoa",685},
  {"Kiribati Republic",686},
  {"New Caledonia",687},
  {"Tuvalu",688},
  {"French Polynesia",689},
  {"Tokelau",690},
  {"Micronesia, Federated States of",691},
  {"Marshall Islands",692},
  {"Kazakhstan",705},
  {"Kyrgyz Republic",706},
  {"Tajikistan",708},
  {"Turkmenistan",709},
  {"Uzbekistan",711},
  {"International Freephone Service",800},
  {"Korea (North)",850},
  {"Hong Kong",852},
  {"Macau",853},
  {"Cambodia",855},
  {"Laos",856},
  {"INMARSAT",870},
  {"INMARSAT (Atlantic-East)",871},
  {"INMARSAT (Pacific)",872},
  {"INMARSAT (Indian)",873},
  {"INMARSAT (Atlantic-West)",874},
  {"Bangladesh",880},
  {"Taiwan, Republic of China",886},
  {"Maldives",960},
  {"Lebanon",961},
  {"Jordan",962},
  {"Syria",963},
  {"Iraq",964},
  {"Kuwait",965},
  {"Saudi Arabia",966},
  {"Yemen",967},
  {"Oman",968},
  {"United Arab Emirates",971},
  {"Israel",972},
  {"Bahrain",973},
  {"Qatar",974},
  {"Bhutan",975},
  {"Mongolia",976},
  {"Nepal",977},
  {"Azerbaijan",994},
  {"Georgia",995},
  {"Comoros",2691},
  {"Liechtenstein",4101},
  {"Slovak Republic",4201},
  {"Guantanamo Bay",5399},
  {"French Antilles",5901},
  {"Cocos-Keeling Islands",6101},
  {"Rota Island",6701},
  {"Tinian Island",6702},
  {"Australian Antarctic Territory",6721},
  {"Norfolk Island",6722},
  {"Unspecified",0xffff}
};
icq_ArrayType icq_MetaOccupation[] = {
  {"Academic", 1},
  {"Administrative", 2},
  {"Art/Entertainment", 3},
  {"College Student", 4},
  {"Computers", 5},
  {"Community & Social", 6},
  {"Education", 7},
  {"Engineering", 8},
  {"Financial Services", 9},
  {"Government", 10},
  {"High School Student", 11},
  {"Home", 12},
  {"ICQ - Providing Help", 13},
  {"Law", 14},
  {"Managerial", 15},
  {"Manufacturing", 16},
  {"Medical/Health", 17},
  {"Military", 18},
  {"Non-Government Organization", 19},
  {"Professional", 20},
  {"Retail", 21},
  {"Retired", 22},
  {"Science & Research", 23},
  {"Sports", 24},
  {"Technical", 25},
  {"University Student", 26},
  {"Web Building", 27},
  {"Other Services", 99},
};

icq_ArrayType icq_MetaPastBackgrounds[] = {
  {"Elementary School", 300},
  {"High School", 301},
  {"College", 302},
  {"University", 303},
  {"Military", 304},
  {"Past Work Place", 305},
  {"Past Organization", 306},
  {"Other", 399},
};

icq_ArrayType icq_MetaAffiliations[] = {
  {"Alumni Org.", 200},
  {"Charity Org.", 201},
  {"Club/Social Org.", 202},
  {"Community Org.", 203},
  {"Cultural Org.", 204},
  {"Fan Clubs", 205},
  {"Fraternity/Sorority", 206},
  {"Hobbyists Org.", 207},
  {"International Org.", 208},
  {"Nature and Environment Org.", 209},
  {"Professional Org.", 210},
  {"Scientific/Technical Org.", 211},
  {"Self Improvement Group", 212},
  {"Spiritual/Religious Org.", 213},
  {"Sports Org.", 214},
  {"Support Org.", 215},
  {"Trade and Business Org.", 216},
  {"Union", 217},
  {"Voluntary Org.", 218},
  {"Other", 299},
};

icq_ArrayType icq_MetaLanguages[] = {
  {"Not Entered", 0},
  {"Arabic", 1},
  {"Bhojpuri", 2},
  {"Bulgarian", 3},
  {"Burmese", 4},
  {"Cantonese", 5},
  {"Catalan", 6},
  {"Chinese", 7},
  {"Croatian", 8},
  {"Czech", 9},
  {"Danish", 10},
  {"Dutch", 11},
  {"English", 12},
  {"Esperanto", 13},
  {"Estonian", 14},
  {"Farsi", 15},
  {"Finnish", 16},
  {"French", 17},
  {"Gaelic", 18},
  {"German", 19},
  {"Greek", 20},
  {"Hebrew", 21},
  {"Hindi", 22},
  {"Hungarian", 23},
  {"Icelandic", 24},
  {"Indonesian", 25},
  {"Italian", 26},
  {"Japanese", 27},
  {"Khmer", 28},
  {"Korean", 29},
  {"Lao", 30},
  {"Latvian", 31},
  {"Lithuanian", 32},
  {"Malay", 33},
  {"Norwegian", 34},
  {"Polish", 35},
  {"Portuguese", 36},
  {"Romanian", 37},
  {"Russian", 38},
  {"Serbian", 39},
  {"Slovak", 40},
  {"Slovenian", 41},
  {"Somali", 42},
  {"Spanish", 43},
  {"Swahili", 44},
  {"Swedish", 45},
  {"Tagalog", 46},
  {"Tatar", 47},
  {"Thai", 48},
  {"Turkish", 49},
  {"Ukrainian", 50},
  {"Urdu", 51},
  {"Vietnamese", 52},
  {"Yiddish", 53},
  {"Yoruba", 54},
  {"Afrikaans", 55},
  {"Bosnian", 56},
  {"Persian", 57},
  {"Albanian", 58},
  {"Armenian", 59},
  {"Punjabi", 60},
  {"Chamorro", 61},
  {"Mongolian", 62},
  {"Mandarin", 63},
  {"Taiwaness", 64},
  {"Macedonian", 65},
  {"Sindhi", 66},
  {"Welsh", 67},
};

icq_ArrayType icq_Genders[] = {
  {"Not Specified", 0},
  {"Female", 1},
  {"Male", 2},
};

void hex_dump(char *data, long size)
{
  long i;
  long x;
  int r=1;
  char d[32];
  unsigned char bfr[64];
  for(i=0, x=0;;i++)
  {
    if(i<size)
    {
      if(x==0)
        printf("%04lx: ", i);
#ifdef _WIN32
      sprintf(d, "%08x", data[i]);
#else
      snprintf(d, 9, "%08x", data[i]);
#endif
      printf("%c%c ", d[6], d[7]);
      bfr[x]=data[i];
      if(bfr[x]<0x20)
        bfr[x]='.';
      if(bfr[x]>0x7f)
        bfr[x]='.';
    }
    else
    {
      if(x==0)
        break;
      else
      {
        printf("   ");
        bfr[x]=' ';
        r=0;
      }
    }
    x++;
    if(!(x<16))
    {
      bfr[x]=0;
      printf("%s\n", bfr);
      x=0;
      if(!r)
        break;
    }
  }
}

/* simple mapping for udp status->tcp status translation function */
struct icq_TCPStatusRec
{
    unsigned long udp_status;
    long tcp_status;
} icq_TCPStatusMap[] = {
    { STATUS_OFFLINE     , 0                        }, 
    { STATUS_ONLINE      , ICQ_TCP_STATUS_ONLINE    }, 
    { STATUS_INVISIBLE   , ICQ_TCP_STATUS_INVISIBLE },
    { STATUS_NA          , ICQ_TCP_STATUS_NA        },
    { STATUS_FREE_CHAT   , ICQ_TCP_STATUS_FREE_CHAT },
    { STATUS_OCCUPIED    , ICQ_TCP_STATUS_OCCUPIED  },
    { STATUS_AWAY        , ICQ_TCP_STATUS_AWAY      },
    { STATUS_DND         , ICQ_TCP_STATUS_DND       },
};

long icq_TCPXlateStatus(unsigned long udp_status)
{
  unsigned int i;
  for(i=0;i<sizeof(icq_TCPStatusMap)/sizeof(struct icq_TCPStatusRec);i++)
    if(icq_TCPStatusMap[i].udp_status==udp_status) 
      return icq_TCPStatusMap[i].tcp_status;
  /* warning: "couldn't find tcp status for %d, assuming 0", udp_status */
  return 0;
}

void icq_FmtLog(icq_Link *icqlink, int level, const char *fmt, ...)
{
  char buffer[2048];
  va_list ap;
  va_start(ap, fmt);
  
  if(!icqlink)
    return;
#ifdef _MSVC_
  _vsnprintf(buffer, 1024, fmt, ap);
#else
  (void)vsnprintf(buffer, 1024, fmt, ap);
#endif
  va_end(ap);

  if(icqlink->icq_Log && icq_LogLevel>=level)
    (*icqlink->icq_Log)(icqlink, time(0L), level, buffer);
}

/**
 * Following functions used by qsort and bsearch to
 * compare 2 pointers to icq_ArrayType object.
 */
int array_code_compare(const void *x, const void *y)
{
  return ((icq_ArrayType*)x)->code - ((icq_ArrayType*)y)->code;
}

const char *icq_GetCountryName(unsigned short code)
{
  icq_ArrayType *res,key;
    
  key.code=code;
  res=bsearch(&key, icq_Countries, sizeof(icq_Countries)/sizeof(icq_ArrayType),
              sizeof(icq_ArrayType), array_code_compare);
    
  return res?res->name:"Unknown";
}

const char *icq_GetMetaOccupationName(unsigned short code)
{
  icq_ArrayType *res,key;
    
  key.code=code;
  res=bsearch(&key, icq_MetaOccupation, sizeof(icq_MetaOccupation)/sizeof(icq_ArrayType),
              sizeof(icq_ArrayType), array_code_compare);
    
  return res?res->name:"Unknown";
}

const char *icq_GetMetaBackgroundName(unsigned short code)
{
  icq_ArrayType *res,key;
    
  key.code=code;
  res=bsearch(&key, icq_MetaPastBackgrounds, sizeof(icq_MetaPastBackgrounds)/sizeof(icq_ArrayType),
              sizeof(icq_ArrayType), array_code_compare);
    
  return res?res->name:"Unknown";
}

const char *icq_GetMetaAffiliationName(unsigned short code)
{
  icq_ArrayType *res,key;
    
  key.code=code;
  res=bsearch(&key, icq_MetaAffiliations, sizeof(icq_MetaAffiliations)/sizeof(icq_ArrayType),
              sizeof(icq_ArrayType), array_code_compare);
    
  return res?res->name:"Unknown";
}

const char *icq_GetMetaLanguageName(unsigned short code)
{
  icq_ArrayType *res,key;
    
  key.code=code;
  res=bsearch(&key, icq_MetaLanguages, sizeof(icq_MetaLanguages)/sizeof(icq_ArrayType),
              sizeof(icq_ArrayType), array_code_compare);
    
  return res?res->name:"Unknown";
}

/********************************************
returns a string describing the status or
a "Error" if no such string exists
*********************************************/
const char *icq_ConvertStatus2Str(unsigned long status)
{
  if((unsigned long)STATUS_OFFLINE == status) /* this because -1 & 0x01FF is not -1 */
    return "Offline";

  if((status & STATUS_INVISIBLE) == STATUS_INVISIBLE)
    return "Invisible";
  else if((status & STATUS_FREE_CHAT) == STATUS_FREE_CHAT)
    return "Free for chat";
  else if((status & STATUS_DND) == STATUS_DND)
    return "Do not disturb";
  else if((status & STATUS_OCCUPIED) == STATUS_OCCUPIED)
    return "Occupied";
  else if((status & STATUS_NA) == STATUS_NA)
    return "Not available";
  else if((status & STATUS_AWAY) == STATUS_AWAY)
    return "Away";
  else if(!(status & 0x01FF))
    return "Online";
  else
    return "Error";
}

int icq_SplitFields(icq_List *strList, const char *str)
{
  char *tmpBuf, *tmp, *ptr;
  int count = 0;
 
  tmpBuf = (char*)malloc(strlen(str)+1);
  strcpy(tmpBuf, str);
  ptr = tmpBuf;
 
  while(ptr)
  {
    char *p;
    tmp = strchr(ptr, 0xFE);
    if(tmp != 0L)
    {
      *tmp = 0;
      tmp++;
    }
    count++;
    p = (char *)malloc(strlen(ptr)+1);
    strcpy(p, ptr);
    icq_ListEnqueue(strList, p);
    ptr = tmp;
  }
 
  free(tmpBuf);
  return count;
}

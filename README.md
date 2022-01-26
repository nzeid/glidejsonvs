# GlideJsonVs

This codebase is dedicated to roughly testing the performance of GlideJson. Emphasis on roughly. The speed of encoding and parsing isn't everything, but it's a decent starting point.

### AMD EPYC(TM) 7542 @2.90GHz

||Parsing (us)|Encoding (us)|
|:---|---:|---:|
|[GlideJson](https://github.com/nzeid/glidejson)|239714|246743|
|[JSON for Modern C++](https://github.com/nlohmann/json)|391730|331619|
|[JsonCpp](https://github.com/open-source-parsers/jsoncpp)|485082|513682|
|[cJSON](https://github.com/DaveGamble/cJSON)|121694|314814|
|[RapidJSON](https://github.com/Tencent/rapidjson)|106889|130648|

## Some Takeaways

- Neither "Json for Modern C++" nor JsonCpp are interested in beating speed tests, but they are very widely used. They serve as an upper bound for performance.
- cJSON and RapidJSON are also popular but very fast. They implement barebones wrappers for JSON structures and use linked lists for containers. This pushes the load of creating useful types and accessible containers to the user app.

## Contributing

Please communicate changes over this project's GitLab/GitHub pages. Bear in mind that the GitLab/GitHub pages are merely mirrors of a separate "official" repository. Any accepted changes will get due authorship and credit.

- [https://github.com/nzeid/glidejsonvs](https://github.com/nzeid/glidejsonvs)
- [https://gitlab.com/nzeid/glidejsonvs](https://gitlab.com/nzeid/glidejsonvs)

## License

Copyright (c) 2021 Nader G. Zeid

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see [https://www.gnu.org/licenses/gpl.html](https://www.gnu.org/licenses/gpl.html).

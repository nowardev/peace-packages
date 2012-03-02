FILE(REMOVE_RECURSE
  "CMakeFiles/pofiles"
  "pt.gmo"
  "pl.gmo"
  "tr.gmo"
  "it.gmo"
  "hu.gmo"
  "de.gmo"
  "ru.gmo"
  "bs.gmo"
  "fr.gmo"
  "sr.gmo"
  "el.gmo"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/pofiles.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)

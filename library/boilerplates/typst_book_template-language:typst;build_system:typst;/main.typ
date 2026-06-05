#import "@preview/wonderous-book:0.1.2": book

#show: book.with(
  title: [|||title|||],
  author: "|||author|||",
  dedication: [|||dedication|||],
  publishing-info: [
    UK Publishing, Inc. \
    6 Abbey Road \
    Vaughnham, 1PX 8A3

    #link("https://example.co.uk/")

    971-1-XXXXXX-XX-X
  ],
)

= Abbey
#lorem(1002)

= Music
#lorem(1500)

= Magic
#lorem(600)

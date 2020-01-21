open Framework;
open QCheckRely;
open Generator.Fantasy;
open Lib.Troll;

let {describe} = extendDescribe(QCheckRely.Matchers.matchers);

describe("Troll Invariance", ({test}) => {
  test("Troll score should be 0 when all elves resurrected", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_arbitrary,
      troll =>
      all_elves_resurrected(troll) |> scoring == 0
    )
    |> expect.ext.qCheckTest;
    ();
  });
  test("Troll score should always be >= 0", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll value should always be positive",
      troll_arbitrary,
      troll => scoring(troll) >= 0
    )
    |> expect.ext.qCheckTest;
    ()
  });
});

 describe("Troll Inverse", ({test}) => {
  test("oops_he_survived should always be inverse of i_got_one", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Oops_he_survived should always be inverse of i_got_one",
      troll_elf_arbitrary,
      ((troll, elf)) => {
        let troll_before_score = scoring(troll);
        let troll_after_score = i_got_one(elf, troll) |> oops_he_survived(elf) |> scoring;
        troll_after_score == troll_before_score
      }
    )
    |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Analogy", ({test}) => {
  test("i_got_one and i_got should be consistent", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="i_got_one and i_got should be consistent",
      troll_elf_int_arbitrary,
      ((troll, elf, number)) => {
        let troll_after_i_got = i_got(number, elf, troll);
        let troll_after_i_got_one = ref(troll);
        for(x in 1 to number) {
          troll_after_i_got_one := i_got_one(elf, troll_after_i_got_one^);
        }

        scoring(troll_after_i_got) == scoring(troll_after_i_got_one^);
      }
    )
    |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Idempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
      QCheck.Test.make(
      ~count=1000,
      ~name="all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
      troll_elf_int_arbitrary,
      ((troll, elf, number)) => {
        let list_kill_after_one = all_elves_of_a_kind_resurrected(elf, troll)
        let list_kill_after_many = ref(troll)
        for(x in 0 to number) {
          list_kill_after_many := all_elves_of_a_kind_resurrected(elf, list_kill_after_many^);
        }

        scoring(list_kill_after_one) == scoring(list_kill_after_many^);
      }
    )
    |> expect.ext.qCheckTest;
    ()
  })
  });

  describe("Troll Metamorphism", ({test}) => {
    test(
      "i_got_one increase kill list when elf die",
      ({expect}) => {
        QCheck.Test.make(
        ~count=1000,
        ~name="all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
        troll_elf_arbitrary,
        ((troll, elf)) => {
          scoring(troll) < scoring(i_got_one(elf, troll));
        }
      )
      |> expect.ext.qCheckTest;
      ()
    })
  });

  describe("Troll Injection", ({test}) => {
    test(
      "i_got_one increase kill list when elf die multy time",
      ({expect}) => {
        QCheck.Test.make(
        ~count=1000,
        ~name="all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
        troll_two_elves_arbitrary,
        ((troll, elf1, elf2)) => {
          let troll_kill_1 = i_got_one(elf1, troll);
          let troll_kill_2 = i_got_one(elf2, troll_kill_1);
          scoring(troll_kill_1) < scoring(troll_kill_2);
        }
      )
      |> expect.ext.qCheckTest;
      ()
    })
  });